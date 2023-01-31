#include "hzpch.h"

#include "GameObject.h"

Vipera::GameObject::GameObject(std::vector<Vertex> vertices, std::vector<int> indices)
	: vertices(vertices), indices(indices)
{

}

Vipera::GameObject Vipera::GameObject::generate_pyramid()
{
    std::vector<Vertex> vertices
    {
        {{-1.0f,  1.0f, -1.0f}, {}, {}},
        {{1.0f,  1.0f, -1.0f }, {}, {}},
        {{1.0f,  1.0f,  1.0f }, {}, {}}, 
        {{-1.0f,  1.0f,  1.0f}, {}, {}},
        {{-1.0f, -1.0f, -1.0f}, {}, {}},
        {{1.0f, -1.0f, -1.0f }, {}, {}},
        {{1.0f, -1.0f,  1.0f }, {}, {}}, 
        {{-1.0f, -1.0f,  1.0f}, {}, {}}
    };

    std::vector<int> indices
    {
        3,1,0,
        2,1,3,
        
        0,5,4,
        1,5,0,

        3,4,7,
        0,4,3,
        
        1,6,5,
        2,6,1,

        2,7,6,
        3,7,2,

        6,4,5,
        7,4,6
    };

    return GameObject(vertices, indices);
}
