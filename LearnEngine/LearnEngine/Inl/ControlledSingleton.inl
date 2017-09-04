#ifndef __CONTROLLED_SINGLETON_INL__
#define __CONTROLLED_SINGLETON_INL__

template<typename T>
T* ControlledSingleton<T>::instance_ = nullptr;

template<typename T>
T& ControlledSingleton<T>::Instance()
{
    return *instance_;
}

template<typename T>
template<typename... TArgs>
void ControlledSingleton<T>::Create(TArgs&&... args)
{
    if (instance_ != nullptr) {
        throw std::logic_error("Logical error: singletone already has an instance. Manualy delete the previous one to create a new..");
    }
    instance_ = T::ConstructionAttorney::ConstructInstance(std::forward<TArgs>(args)...);
}

template<typename T>
bool ControlledSingleton<T>::IsCreated()
{
    return instance_ != nullptr;
}

template<typename T>
void ControlledSingleton<T>::Delete()
{
    delete instance_;
    instance_ = nullptr;
}

#endif