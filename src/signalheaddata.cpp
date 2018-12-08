#include <set>

#include "signalheaddata.hpp"

namespace Signalbox {
  std::vector<ControlledItemDataError> SignalHeadData::GetErrors() const {
    std::vector<ControlledItemDataError> result;

    if( this->id == ItemId(0) ) {
      ControlledItemDataError e;
      e.message = "Invalid id";
      result.push_back(e);
    }

    if( (this->aspectCount < 2) || (this->aspectCount > 4) ) {
      ControlledItemDataError e;
      e.message = "Invalid aspectCount";
      result.push_back(e);
    }

    if( result.size() == 0 ) {
      auto aspectErrs = this->GetAspectErrors();
      result.insert( result.end(), aspectErrs.begin(), aspectErrs.end() );

      auto pinErrs = this->GetPinErrors();
      result.insert( result.end(), pinErrs.begin(), pinErrs.end() );
    }
      
    return result;
  }

  std::vector<ControlledItemDataError> SignalHeadData::GetAspectErrors() const {
    std::vector<ControlledItemDataError> result;

    if( this->pinData.count(SignalHeadPins::Red) != 1 ) {
      ControlledItemDataError e;
      e.message = "No Red aspect";
      result.push_back(e);
    }

    if( this->pinData.count(SignalHeadPins::Green) != 1 ) {
      ControlledItemDataError e;
      e.message = "No Green aspect";
      result.push_back(e);
    }

    if( this->pinData.count(SignalHeadPins::Yellow1) == 1 ) {
      if( this->aspectCount < 3 ) {
	ControlledItemDataError e;
	e.message = "Yellow1 aspect not allowed";
	result.push_back(e);
      }
    } else {
      if( this->aspectCount >= 3 ) {
	ControlledItemDataError e;
	e.message = "No Yellow1 aspect";
	result.push_back(e);
      }
    }

    if( this->pinData.count(SignalHeadPins::Yellow2) == 1 ) {
      if( this->aspectCount < 4 ) {
	ControlledItemDataError e;
	e.message = "Yellow2 aspect not allowed";
	result.push_back(e);
      }
    } else {
      if( this->aspectCount >= 4 ) {
	ControlledItemDataError e;
	e.message = "No Yellow2 aspect";
	result.push_back(e);
      }
    }
    
    return result;
  }

  std::vector<ControlledItemDataError> SignalHeadData::GetPinErrors() const {
    std::vector<ControlledItemDataError> result;

    std::set<std::string> uniquePins;

    for( auto it=this->pinData.begin(); it!=this->pinData.end(); ++it ) {
      uniquePins.insert(it->second);
    }

    if( uniquePins.size() != this->pinData.size() ) {
      ControlledItemDataError e;
      e.message = "Duplicate pin values present";
      result.push_back(e);
    }
    
    return result;
  }

  ControlledItemFactory* SignalHeadData::GetFactory(ControlledItemFactorySelector* factorySelector) const {
    return factorySelector->GetSignalHeadFactory();
  }
}
