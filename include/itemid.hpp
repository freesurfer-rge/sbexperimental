#pragma once

#include <chrono>
#include <iostream>
#include <random>

namespace Signalbox {
  class ItemId {
  public:
    typedef uint32_t IdType;

    ItemId() : id(0) {}
    
    ItemId(IdType idVal) : id(idVal) {}

    void Get(IdType* val) const {
      *val = this->id;
    }

    IdType Get() const {
      return this->id;
    }

    void Set(const IdType val) {
      this->id = val;
    }

    void Parse(std::string str);
    
    bool operator<(const ItemId item) const {
      return this->id < item.id;
    }

    bool operator==(const ItemId item) const {
      return this->id == item.id;
    }

    bool operator!=(const ItemId item) const {
      return !((*this)==item);
    }

    std::string ToString() const;

    static ItemId Nil() {
      return ItemId();
    }

    static ItemId Random() {
      unsigned long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
      std::default_random_engine rand(seed);
      std::uniform_int_distribution<IdType> dist;

      return ItemId(dist(rand));
    }
  private:
    IdType id;
  };

  std::ostream& operator<<(std::ostream& os, const Signalbox::ItemId& item);
  std::istream& operator>>(std::istream& is, Signalbox::ItemId& item);
}


