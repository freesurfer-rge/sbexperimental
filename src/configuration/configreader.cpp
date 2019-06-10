#include <sstream>

#include <boost/filesystem.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include "configuration/utils.hpp"
#include "configuration/xercesstringdeleter.hpp"
#include "configuration/configreader.hpp"

#include "digitaloutputpindata.hpp"
#include "signalheaddata.hpp"
#include "trackcircuitmonitordata.hpp"
#include "servoturnoutmotordata.hpp"

namespace Signalbox {
  namespace Configuration {
    ConfigReader::ConfigReader( const std::string& filename ) : XercesGuard(),
								configFileParser() {
      if( !boost::filesystem::exists(filename) ) {
	throw std::runtime_error( filename + " NOT FOUND" );
      }
      
      this->configFileParser = std::unique_ptr<xercesc::XercesDOMParser>(new xercesc::XercesDOMParser);
      
      // Configure the parser
      this->configFileParser->setValidationScheme( xercesc::XercesDOMParser::Val_Never );
      this->configFileParser->setDoNamespaces( false );
      this->configFileParser->setDoSchema( false );
      this->configFileParser->setLoadExternalDTD( false );
      
      this->configFileParser->parse( filename.c_str() );
    }
    
    void ConfigReader::ReadRailTrafficControl( RailTrafficControlData& rtcData ) {
      // Get the root element of the document
      xercesc::DOMElement* elementSignalbox = this->GetSignalBoxElement();
      
      auto TAG_RailTrafficControl = std::string("RailTrafficControl");
      auto TAG_Host = std::string("Host");
      auto TAG_Port = std::string("Port");
      
      auto rtcElement = GetSingleElementByName( elementSignalbox,
						TAG_RailTrafficControl );
      
      // Fetch the host data
      rtcData.host = GetSingleElementTextByName( rtcElement, TAG_Host );
      
      // On to the port
      auto portString = GetSingleElementTextByName( rtcElement, TAG_Port );
      auto portNumber = std::stoul(portString);
      if( portNumber > std::numeric_limits<uint16_t>::max() ) {
	throw std::runtime_error("Invalid Port for RailTrafficControl");
      }
      rtcData.port = std::stoul(portString);
    }

    void ConfigReader::ReadI2CData( I2CBusData& i2cData ) {
      // Make sure we have an empty list
      i2cData.devices.clear();

      // Get the root element of the document
      xercesc::DOMElement* elementSignalbox = this->GetSignalBoxElement();
      
      auto TAG_I2C = std::string("I2C");
      auto TAG_I2CDevice = StrToXMLCh("I2CDevice");

      auto i2cElement = GetSingleElementByName( elementSignalbox,
						TAG_I2C );

      auto i2cDeviceList = i2cElement->getChildNodes();
      for( XMLSize_t i=0; i<i2cDeviceList->getLength(); ++i ) {
	auto currentNode = i2cDeviceList->item(i);

	if( IsElementNode(currentNode) ) {
	  // Cast node to an element
	  auto currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);

	  if( xercesc::XMLString::equals(currentElement->getTagName(), TAG_I2CDevice.get() ) ) {
	    I2CDeviceData data;
	    data.kind = Configuration::GetAttributeByName(currentElement, "kind");

	    std::string busString = Configuration::GetAttributeByName(currentElement, "bus" );
	      data.bus = std::stoul(busString, nullptr, 0);
	    std::string addrString = Configuration::GetAttributeByName(currentElement, "address" );
	    data.address = std::stoul(addrString, nullptr, 0);
	    data.name = Configuration::GetAttributeByName(currentElement, "name");

	    PopulateSettingsMap( currentElement, data.settings );

	    i2cData.devices.push_back(data);
	  }
	}
      }
    }
    
    void ConfigReader::ReadControlledItems( std::vector<std::unique_ptr<ControlledItemData>>& items ) {
      // Make sure we have an empty list
      items.clear();
      
      // Get the root element of the document
      xercesc::DOMElement* elementSignalbox = this->GetSignalBoxElement();
      
      auto TAG_ControlledItems = std::string("ControlledItems");
      auto TAG_SignalHead = StrToXMLCh("SignalHead");
      auto TAG_TrackCircuitMonitor = StrToXMLCh("TrackCircuitMonitor");
      auto TAG_ServoTurnoutMotor = StrToXMLCh("ServoTurnoutMotor");
      
      auto elementControlledItems = GetSingleElementByName( elementSignalbox,
							    TAG_ControlledItems );
      
      auto controlledItems = elementControlledItems->getChildNodes();
      for( XMLSize_t i=0; i<controlledItems->getLength(); ++i ) {
	std::unique_ptr<ControlledItemData> item(nullptr);
	auto currentNode = controlledItems->item(i);
	
	if( IsElementNode(currentNode) ) {
	  // Cast node to an element
	  auto currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
	  
	  if( xercesc::XMLString::equals(currentElement->getTagName(), TAG_SignalHead.get() ) ) {
	    item.reset( this->ReadSignalHead(currentElement) );
	  } else if( xercesc::XMLString::equals(currentElement->getTagName(), TAG_TrackCircuitMonitor.get() ) ) {
	    item.reset( this->ReadTrackCircuitMonitor(currentElement) );
	  } else if( xercesc::XMLString::equals(currentElement->getTagName(), TAG_ServoTurnoutMotor.get() ) ) {
	    item.reset( this->ReadServoTurnoutMotor(currentElement) );
	  } else {
	    throw std::runtime_error("Unknown tag name");
	  }
	  
	  // Common code to sort out the id attribute
	  item->id.Parse(GetIdAttribute(currentElement));
	}
	
	// Add to the list
	if( item.get() != nullptr ) {
	  // Have to 'move' since we can't copy a unique_ptr
	  items.push_back(std::move(item));
	}
      }
    }
    
    xercesc::DOMElement* ConfigReader::GetSignalBoxElement() {
      auto TAG_SignalBox = StrToXMLCh("SignalBox");
      
      // The following remains owned by the parser object
      auto xmlDoc = this->configFileParser->getDocument();
      
      auto docElement = xmlDoc->getDocumentElement();
      if( docElement == nullptr ) {
	throw std::runtime_error("Empty document");
      }
      
      if( !xercesc::XMLString::equals(docElement->getTagName(), TAG_SignalBox.get()) ) {
	throw std::runtime_error("Root element is not SignalBox");
      }
      
      return docElement;
    }
    
    ControlledItemData* ConfigReader::ReadSignalHead(xercesc::DOMElement* currentElement ) {
      std::unique_ptr<SignalHeadData> signal( new SignalHeadData );
      
      auto aspectCount_attr = GetAttributeByName(currentElement, "aspectCount");
      signal->aspectCount = std::stoi(aspectCount_attr);
      
      auto outputPins = currentElement->getChildNodes();
      // For some reason, the length of this list is 9.....
      for( XMLSize_t iPin=0; iPin<outputPins->getLength(); iPin++ ) {
	auto pinNode = outputPins->item(iPin);
	
	if( IsElementNode(pinNode) ) {
	  // Cast node to an element
	  auto currentPin = dynamic_cast<xercesc::DOMElement*>(pinNode);
	  
	  if( IsOutputPin(currentPin) ) {
	    DigitalOutputPinData pin;
	    pin.id = Configuration::GetIdAttribute(currentPin);
	    pin.control = Configuration::GetAttributeByName(currentPin, "control");
	    
	    auto controlPin = StringToSignalHeadPins(pin.control);	  
	    signal->pinData[controlPin] = pin.id;
	  }
	}
      }
      
      // This gets the raw pointer, and stops the unique_ptr from managing it
      return signal.release();
    }
    
    ControlledItemData* ConfigReader::ReadTrackCircuitMonitor(xercesc::DOMElement* currentElement ) {
      std::unique_ptr<TrackCircuitMonitorData> tc( new TrackCircuitMonitorData );
      
      auto children = currentElement->getChildNodes();
      
      // We don't have a schema defined for the XML document yet, but we
      // shall expect it to require that a TrackCircuit has a single OutputPin
      for( XMLSize_t i=0; i<children->getLength(); i++ ) {
	auto child = children->item(i);
	
	if( IsElementNode(child) ) {
	  auto nxtElement = dynamic_cast<xercesc::DOMElement*>(child);
	  
	  if( IsInputPin(nxtElement) ) {
	    DigitalInputPinData pin;
	    
	    pin.id = GetIdAttribute(nxtElement);
	    pin.sensor = GetAttributeByName(nxtElement, "sensor");
	    
	    PopulateSettingsMap( nxtElement, pin.settings );
	    
	    // Put it into the data structure
	    tc->inputPin = pin;
	  }
	}
      }
      
      return tc.release();
    }

    ControlledItemData* ConfigReader::ReadServoTurnoutMotor( xercesc::DOMElement* currentElement ) {
      std::unique_ptr<ServoTurnoutMotorData> tm( new ServoTurnoutMotorData );

      auto straight_attr = GetAttributeByName(currentElement, "straight");
      tm->straight = std::stoul(straight_attr);

      auto curved_attr = GetAttributeByName(currentElement, "curved");
      tm->curved = std::stoul(curved_attr);
      
      auto children = currentElement->getChildNodes();
      // Don't have a schema defined, but should contain one PWMChannel node
       for( XMLSize_t i=0; i<children->getLength(); i++ ) {
	auto child = children->item(i);
	
	if( IsElementNode(child) ) {
	  auto nxtElement = dynamic_cast<xercesc::DOMElement*>(child);

	  if( IsPWMChannel(nxtElement) ) {
	    tm->pwmChannelRequest.controller = GetAttributeByName(nxtElement, "controller");
	    tm->pwmChannelRequest.controllerData = GetAttributeByName(nxtElement, "controllerData" );
	  }
	}
       }
      
      return tm.release();
    }
  }
}
