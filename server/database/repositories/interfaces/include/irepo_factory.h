#pragma once

#include <memory>

#include "itask_repository.h"
#include "iuser_repository.h"

namespace database {
namespace repo {

class IRepoFactory {
   public:
    virtual ~IRepoFactory() = default;
};

}  // namespace repo
}  // namespace database
