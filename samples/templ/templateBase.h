#pragma once

namespace voxlog
{
namespace samples
{
namespace templ
{
namespace
{
// crtp
template <class Derived>
struct CRTPBaseStruct
{
    void interCall()
    {
        static_cast<Derived*>(this)->implementation();
    }
};

struct CRTPBStruct : CRTPBaseStruct<CRTPBStruct>
{
    void implementation()
    {
    }
};

} // namespace


} // namespace templ
} // namespace samples
} // namespace voxlog