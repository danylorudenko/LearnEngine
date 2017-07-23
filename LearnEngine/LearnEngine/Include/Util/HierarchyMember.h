#ifndef __HIERARCHY_MEMBER_H__
#define __HIERARCHY_MEMBER_H__

#include <algorithm>
#include <memory>
#include <list>

template<typename T>
class HierarchyMember
{
public:
    using ChildrenContainer = std::list<HierarchyMember*>;

    HierarchyMember (HierarchyMember* parent) :
        parent_(parent)
    {
        if (parent_) {
            parent->AddChildToListWithIndex(this);
        }
    }

    virtual ~HierarchyMember()
    {
        std::for_each(children_.begin(), children_.end(),
            [](HierarchyMember* child) {
            delete child;
        });
    }
    
    T& Parent()
    {
        return static_cast<T>(parent_);
    }

    void SetParent(HierarchyMember* parent)
    {
        this->parent_->children_.remove_if(
            [this](HierarchyMember* candidate) {
            return candidate == this;
        });
        // As we now may have gaps in children index order we chould update them.
        UpdateIndicies();

        this->parent_ = parent;
        AddChildToListWithIndex(this);
    }

    std::size_t AddChildToListWithIndex(HierarchyMember* new_member)
    {
        new_member->member_index_ = children_.size();
        children_.push_back(new_member);
        return new_member->member_index_;
    }

protected:
    void UpdateIndicies()
    {
        std::size_t index = 0;
        std::for_each(children_.begin(), children_.end(),
            [&index](HierarchyMember* child) {
            child->member_index_ = index++;
        });
    }

protected:
    std::size_t             member_index_;
    HierarchyMember*        parent_;

    ChildrenContainer       children_;
};

#endif