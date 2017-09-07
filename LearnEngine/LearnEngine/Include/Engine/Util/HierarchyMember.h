#ifndef __HIERARCHY_MEMBER_H__
#define __HIERARCHY_MEMBER_H__

#include <algorithm>
#include <memory>
#include <list>

namespace Engine
{

template<typename T>
class HierarchyMember
{
public:
    using ChildrenContainer = std::list<HierarchyMember*>;

    HierarchyMember (HierarchyMember* parent);

    virtual ~HierarchyMember();
    
    T& Parent();

    void SetParent(HierarchyMember* parent);


protected:
    void UpdateIndicies();

    std::size_t AddChildToListWithIndex(HierarchyMember* new_member);

protected:
    std::size_t             member_index_;
    HierarchyMember*        parent_;

    ChildrenContainer       children_;
};

} // namespace Engine

#include <Engine\Inl\HierarchyMember.inl>

#endif