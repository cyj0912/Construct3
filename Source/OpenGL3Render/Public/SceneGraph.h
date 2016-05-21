//Experimental scene graph

#pragma once
#include <Core.h>
#include <vector>
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

C3_NAMESPACE_BEGIN
class FSceneGraph;
class FRenderModel;
class FShader;
class RMesh;

class SGNode
{
public:
	FSceneGraph* Owner;
    SGNode* Parent;
    std::vector<SGNode*> Children;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

class SGCamera : public SGNode
{
    glm::mat4 MView;
    glm::mat4 MProjection;
	int Width, Height;
public:
    SGCamera(int w, int h) : Width(w), Height(h)
    {
        //Default position - look at origin from (0, 0, 25)
        MView = glm::lookAt(glm::vec3(0, 0, 10.0f), glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));
		MProjection = glm::perspective(90.0f / 180.0f * 3.141592654f, (float)w / (float)h, 0.1f, 1000.0f);
    }

	void Resize(int w, int h)
    {
		Width = w;
		Height = h;
    }

    void LookAt(const glm::vec3& from, const glm::vec3& to)
    {
        MView = glm::lookAt(from, to, glm::vec3(0.0f, 1.0f, 0.0f));
    }

	void Uniform(const glm::mat4& model);

	void Update() override
	{
	}

	void Render() override
	{
	}
};

class FSceneGraph
{
	SGNode* RootNode;
	SGCamera* ActiveCamera;
public:
	SGNode* const& GetRootNode() const
	{
		return RootNode;
	}

	void SetRootNode(SGNode* const root_node)
	{
		RootNode = root_node;
	}

	SGCamera* const& GetActiveCamera() const
	{
		return ActiveCamera;
	}

	void SetActiveCamera(SGCamera* const active_camera)
	{
		ActiveCamera = active_camera;
	}

	FSceneGraph() : RootNode(nullptr), ActiveCamera(nullptr)
	{
	}

	void Update()
	{
		if (RootNode == nullptr)
			return;
		std::stack<SGNode*> stack;
		stack.push(RootNode);
		while(!stack.empty())
		{
			SGNode* currNode = stack.top();
			stack.pop();
			for(SGNode* n : currNode->Children)
			{
				stack.push(n);
			}
			currNode->Update();
		}
	}

	void Render()
	{
		if (RootNode == nullptr)
			return;
		std::stack<SGNode*> stack;
		stack.push(RootNode);
		while (!stack.empty())
		{
			SGNode* currNode = stack.top();
			stack.pop();
			for (SGNode* n : currNode->Children)
			{
				stack.push(n);
			}
			currNode->Render();
		}
	}
};

struct FBoundingRect
{
	glm::vec2 BtmLeft, TopRight;
};

//Lazy
class SGObject : public SGNode
{
	FRenderModel* Model;
	bool bModelReady;
	glm::mat4 MTransform;
	glm::vec3 Scale;
	glm::quat Rotation;
	glm::vec3 Position;
public:
	SGObject()
	{
		Reset();
	}

	void Reset()
	{
		Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		Rotation = glm::quat();
		Position = glm::vec3(0.0f);
		Model = nullptr;
		bModelReady = false;
	}

	void Move(float x, float y, float z)
	{
		Position.x += x;
		Position.y += y;
		Position.z += z;
	}

	const glm::mat4& GetTransform()
	{
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);
		glm::mat4 roatation = glm::mat4_cast(Rotation);
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), Position);
		MTransform = translate * roatation * scale;
		return MTransform;
	}

	const glm::vec3& GetScale() const
	{
		return Scale;
	}

	void SetScale(const glm::vec3& scale)
	{
		Scale = scale;
	}

	const glm::quat& GetRotation() const
	{
		return Rotation;
	}

	void SetRotation(const glm::quat& rotation)
	{
		Rotation = rotation;
	}

	const glm::vec3& GetPosition() const
	{
		return Position;
	}

	void SetPosition(const glm::vec3& position)
	{
		Position = position;
	}

	void Update() override
	{
		GetTransform();
	}

	void Render() override;
	void LoadModelFromResource(const FAutoRef<RMesh>& rmesh);

	void DeleteModel();
};
C3_NAMESPACE_END
