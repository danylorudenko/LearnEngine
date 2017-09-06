#ifndef __NOT_IMPLEMENTED_EXC_H__
#define __NOT_IMPLEMENTED_EXC_H__

#include <stdexcept>

class not_implemented_exc : public std::exception
{
public:
    not_implemented_exc                 (const char* const message);

    virtual const char*         what    () const override;
private:
    const char* info_;
};

#endif