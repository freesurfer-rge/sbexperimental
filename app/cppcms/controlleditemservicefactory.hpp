#pragma once

#include <cppcms/applications_pool.h>

#include "controlleditemfetcher.hpp"

namespace Signalbox {
  class ControlledItemServiceFactory : public cppcms::application_specific_pool {
  public:
    ControlledItemServiceFactory( ControlledItemFetcher* cif ) :
      cppcms::application_specific_pool(),
      fetcher(cif) {}

    // Remove copy constructor and assignment to protect pointer member
    ControlledItemServiceFactory(const ControlledItemServiceFactory&) = delete;
    ControlledItemServiceFactory operator=(const ControlledItemServiceFactory&) = delete;
  protected:
    virtual cppcms::application* new_application (cppcms::service &srv) override;
    
  private:
    ControlledItemFetcher* fetcher;
  };
}
