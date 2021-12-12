#version 330 core

/* Shader Outputs */
out vec4 color;
// out vec4 shade;

/* Shader Inputs */
in vec3 Normal;
in vec3 FragPos;
in vec2 uv;

/* Uniforms */
/* View */
uniform vec3 viewPos; // Is it possible to take this from another uniform or input??

/* Light */
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float diffuseIntensity;
uniform float specularIntensity;
uniform float ambientIntensity;

/* Texture */
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;

uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main()
{
	/* Ambient Light */
	vec3 ambient = ambientIntensity * lightColor;

	/* Diffuse Light */
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

	/* If the angle between both vectors is greater than 90 degrees then the result */
	/* of the dot product will actually become negative and we end up with a negative diffuse component. */
	/* For that reason we use the max function that returns the highest of */
	/* both its parameters to make sure the diffuse component (and thus the colors) never become negative. */
	float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseIntensity * lightColor;

	/* Specular Light */
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm); /* lightDir points from the fragment to the light. reflect() expects the other way around. */
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); /* The 32 is the shininess of the material */
    vec3 specular = specularIntensity * spec * lightColor;
	
	vec3 resultColor = (ambient + diffuse + specular) * vec3(texture2D(texture_diffuse1, uv));
	
	color = vec4(resultColor, 1.0);
	// shade = texture2D(texture_diffuse2, uv);
}