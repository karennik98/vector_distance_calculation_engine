//#include <cuda.h>
//#include <cuda_runtime.h>
//
//namespace dce {
//    namespace metrics {
//        namespace cuda {
//            namespace hamming {
//                template<typename TValue>
//                __global__ void distance(size_t size, TValue *vec_1, TValue *vec_2, TValue *distance);
//
//                template<typename TValue, typename TVectorIter>
//                TValue cuda_distance(size_t size, TVectorIter iter1, TVectorIter iter2);
//            }
//        }
//    }
//}