#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include "..\Component.h"

class Script : public Component
{
public:
    Script                                                  ();
    Script                                                  (const Script& rhs);
    Script                                                  (Script&& rhs);

    Script&                     operator=                   (const Script& rhs);
    Script&                     operator=                   (Script&& rhs);


    void                        SetTicking                  (bool value);

protected:
    virtual void                RegisterInSystem            () override;
    virtual void                UnregisterFromSystem        () override;

    virtual void                OnRegistered                ();
    virtual void                OnUnregistered              ();
    virtual void                Tick                        ();

protected:
    bool                        enable_ticking_;
};

#endif