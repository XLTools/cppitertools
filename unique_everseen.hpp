#ifndef ITER_UNIQUE_EVERSEEN_HPP_
#define ITER_UNIQUE_EVERSEEN_HPP_

#include "internal/iterbase.hpp"
#include "filter.hpp"

#include <type_traits>
#include <functional>
#include <utility>
#include <unordered_set>
#include <iterator>

namespace iter {
  namespace impl {
    struct UniqueEverseenFn : Pipeable<UniqueEverseenFn> {
      template <typename Container>
      auto operator()(Container&& container) const {
        using elem_type = impl::iterator_deref<Container>;
        auto func = [elem_seen = std::unordered_set<std::decay_t<elem_type>>()](
            const elem_type& e) mutable {
          return elem_seen.insert(e).second;
        };
        return filter(func, std::forward<Container>(container));
      }
    };
  }

  constexpr impl::UniqueEverseenFn unique_everseen{};
}

#endif
