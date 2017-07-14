#include "..\Include\Util\CustomException\not_implemented_exc.h"

not_implemented_exc::not_implemented_exc(const char* const message)
{
    info_ = message;
}

const char* not_implemented_exc::what() const
{
    return info_;
}