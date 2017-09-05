#ifndef __ENTITY_INL__
#define __ENTITY_INL__

template<typename TComponent>
TComponent* Entity::GetComponent()
{
	for (auto component : components_) {
		if (auto casted_component = dynamic_cast<TComponent*>(component)) {
			return casted_component;
		}
	}

	return nullptr;
}

// Adds component to the internal list and sets its owner to self.
// Performs registration of the component in the contolling system, if needed.
template<typename TComponent>
TComponent* Entity::AddComponent()
{
	TComponent* component = ComponentFactory<TComponent>::ConstructComponent(this);
	components_.push_back(component);

	return component;
}

// Removes pointer to the component and unregisters component from engines subsystems, if needed.
// Removes owner pointer for the component.
template<typename TComponent>
void Entity::RemoveComponent(TComponent* to_remove)
{
	components_.remove_if(
		[component](TComponent* candidate) {
		if (component == candidate) {
			ComponentFactory<TComponent>::DestroyComponent(component);
			return true;
		}
		else {
			return false;
		}
	});
}

#endif