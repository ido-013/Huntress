template <typename T>
inline void ComponentManager<T>::AddComp(T* comp)
{
    component.push_back(comp);
}

template<typename T>
inline void ComponentManager<T>::DelComp(T* comp)
{
    for (auto it = component.begin(); it != component.end(); it++)
    {
        if ((*it) == comp)
        {
            component.erase(it);
            return;
        }
    }
}

template <typename T>
ComponentManager<T>::ComponentManager() {}

template <typename T>
ComponentManager<T>::~ComponentManager() {}

template <typename T>
void ComponentManager<T>::Update()
{
    for (auto it : component)
    {
        it->Update();
    }
}