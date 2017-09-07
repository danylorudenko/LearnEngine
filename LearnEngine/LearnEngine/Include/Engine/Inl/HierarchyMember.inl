#ifndef __HIERARCHY_MEMBER_INL__
#define __HIERARHCY_MEMBER_INL__

#include <stdexcept>

namespace Engine
{

template<typename T>
HierarchyMember<T>::HierarchyMember(HierarchyMember<T>* parent) :
    parent_(parent)
{
    if (parent_) {
        parent->AddChildToListWithIndex(this);
    }
}

template<typename T>
HierarchyMember<T>::~HierarchyMember()
{
    std::for_each(children_.begin(), children_.end(),
        [](HierarchyMember* child) {
        delete child;
    });
}

template<typename T>
T& HierarchyMember<T>::Parent()
{
    return static_cast<T&>(parent_);
}

template<typename T>
void HierarchyMember<T>::SetParent(HierarchyMember<T>* parent)
{
    this->parent_->children_.remove_if(
        [this](HierarchyMember* candidate) {
        return candidate == this;
    });
    // As we now may have gaps in children index order we chould update them.
    this->parent_->UpdateIndicies();

    this->parent_ = parent;
    AddChildToListWithIndex(this);
}

template<typename T>
void HierarchyMember<T>::UpdateIndicies()
{
    std::size_t index = 0;
    std::for_each(children_.begin(), children_.end(),
        [&index](HierarchyMember* child) {
        child->member_index_ = index++;
    });
}

template<typename T>
std::size_t HierarchyMember<T>::AddChildToListWithIndex(HierarchyMember* new_member)
{
    new_member->member_index_ = children_.size();
    children_.push_back(new_member);
    new_member->parent_ = this;
    return new_member->member_index_;
}

} // namespace Engine

#endif