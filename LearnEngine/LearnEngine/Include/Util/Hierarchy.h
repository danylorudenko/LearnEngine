#ifndef __HIERARCHY_MEMBER_H__
#define __HIERARCHY_MEMBER_H__

#include <memory>
#include <list>

template<typename T>
class HierarchyMember
{
public:
    using ChildrenContainer = std::list<HierarchyMember>;
    using ContentType       = T;

    HierarchyMember (T* content, HierarchyMember* parent) :
        content_(content),
        parent_(parent)
    {
        parent->AddChildToList(this);
    }
    
    T& Content()
    {
        return *content_;
    }
    void SetParent(HierarchyMember* member) = 0;

protected:
    std::size_t AddChildToList(HierarchyMember* new_member)
    {
        std::size_t new_member_index = children_.size();
        children_.push_back(*new_member);
    }

protected:
    std::size_t             member_index_;
    std::unique_ptr<T>      content_;
    HierarchyMember*        parent_;

    ChildrenContainer       children_;
};

#endif