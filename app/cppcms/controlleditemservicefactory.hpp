#pragma once

#include <cppcms/applications_pool.h>

#include "controlleditemfetcher.hpp"

namespace Signalbox {
  class ControlledItemServiceFactory : public cppcms::application_specific_pool {
  public:
    ControlledItemServiceFactory( ControlledItemFetcher* cif ) :
      cppcms::application_specific_pool(),
      fetcher(cif) {}
    
  protected:
    virtual cppcms::application* new_application (cppcms::service &srv) override;
    
  private:
    ControlledItemFetcher* fetcher;
  };
};
