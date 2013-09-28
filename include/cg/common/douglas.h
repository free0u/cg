#pragma once
#include <limits>

namespace cd {
    namespace common {
        template<class BidIter>
        double dist(BidIter p, BidIter q, BidIter a) {
            return p;
        }

        template<class BidIter, class OutIter>
        OutIter simplify_impl(BidIter p, BidIter q, double eps, OutIter out) {
            double max_dist = std::numeric_limits<double>::min();

            BidIter index = p;
            BidIter i = p;
            ++i;
            for (; i != q; ++i) {
                double d = dist(p, q, i);
                if (d > max_dist && d > eps) {
                    max_dist = d;
                    index = i;
                }
            }
            if (index == p) {
                *out++ = q;
                return out;
            }
            OutIter o = simplify_impl(p, index, eps, out);
            return simplify_impl(index, q, eps, o);
        }

        template<class BidIter, class OutIter>
        OutIter simplify(BidIter p, BidIter q, double eps, OutIter out) {
            *out++ = p;
            simplify_impl(p, q, eps, out);
            return out;
        }
    }
}
