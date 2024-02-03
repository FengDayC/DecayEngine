#include <glm\glm.hpp>
#include "Core.h"
#include "Renderer\Texture.h"

namespace Decay
{
	struct PointLight
	{
		glm::vec3 Position;
		glm::vec3 Color;
		float Radius;
		float Intensity;
	};

	struct DirectionalLight
	{
		glm::vec3 Direction;
		glm::vec3 Color;
		float Intensity;
	};

	struct SpotLight
	{
		glm::vec3 Position;
		glm::vec3 Direction;
		glm::vec3 Color;
		float Radius;
		float Intensity;
		float InnerAngle;
		float OuterAngle;
	};

	struct Environment
	{
		S_PTR<Texture2D> IrradienceMap;
		glm::vec3 AmbientColor;
	};
}