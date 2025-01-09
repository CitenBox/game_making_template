    #version 330

    in vec4 vertColor;
    in vec2 texCoord;
    in vec3 normal;
    in vec3 fragPos;

    out vec4 color;

    const int MAX_POINT_LIGHTS = 3;
    const int MAX_SPOT_LIGHTS = 3;

    struct Light
    {
        vec3 color;
        float ambientIntensity;
        float diffuseIntensity;
    };

    struct DirectionalLight
    {
        Light base;
        vec3 direction;
    };

    struct PointLight
    {
        Light base;
        vec3 position;
        float constant;
        float linear;
        float exponent;
    };

    struct SpotLight
    {
        PointLight base;
        vec3 direction;
        float edge;
    };

    struct Material
    {
        float specularIntensity;
        float shininess;
    };

    uniform int pointLightCount;
    uniform int spotLightCount;

    uniform DirectionalLight directionalLight;
    uniform PointLight pointLights[MAX_POINT_LIGHTS];
    uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

    uniform sampler2D theTexture;
    uniform Material material;

    uniform vec3 eyePosition;

    vec4 CalcLightByDirection(Light light, vec3 direction)
    {
        vec4 ambientColor = vec4(light.color, 1.f) * light.ambientIntensity;

        float diffuseFactor = max(dot(normalize(normal), normalize(direction)), 0.f);
        vec4 diffuseColor = vec4(light.color, 1.f) * light.ambientIntensity * diffuseFactor;

        vec4 specularColor = vec4(0, 0, 0, 0);

        if(diffuseFactor > 0.f)
        {
            vec3 fragToEye = normalize(eyePosition - fragPos);
            vec3 reflectedVertex = normalize(reflect(direction, normalize(normal)));

            float specularFactor = dot(fragToEye, reflectedVertex);

            if(specularFactor > 0.f)
            {
                specularFactor = pow(specularFactor, material.shininess);
                specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.f);
            }
        }

        return  ambientColor + diffuseColor + specularColor;
    }

    vec4 CalcDirectionalLight()
    {
        return CalcLightByDirection(directionalLight.base, directionalLight.direction);
    }

    vec4 CalcPointLight(PointLight light)
    {
        vec3 direction = fragPos - light.position;
        float distance = length(direction);
        direction = normalize(direction);

        vec4 lightColor = CalcLightByDirection(light.base, direction);
        float attenuation = light.exponent * distance * distance +
        light.linear * distance +
        light.constant;

        return (lightColor / attenuation);
    }
//fuck me suck me
    vec4 CalcSpotLight(SpotLight light)
    {
        vec3 rayDirection = normalize(fragPos - light.base.position);
        float slFactor = dot(rayDirection, normalize(light.direction));

        if(slFactor > light.edge)
        {
            vec4 pointLightColor = CalcPointLight(light.base);
            return pointLightColor * (1.f - (1.f - slFactor) * (1.f/(1.f - light.edge)));
        }
        else
        {
            return vec4(0);
        }
    }

    vec4 CalcPointLights()
    {
        vec4 totalColor = vec4(0, 0, 0, 0);
        for(int i = 0; i < pointLightCount; i++)
        {
            totalColor += CalcPointLight(pointLights[i]);
        }

        return totalColor;
    }

    vec4 CalcSpotLights()
    {
        vec4 totalColor = vec4(0);
        for(int i = 0; i < spotLightCount; i++)
        {
            totalColor += CalcSpotLight(spotLights[i]);
        }

        return totalColor;
    }

    void main()
    {
        vec4 finalColor = CalcDirectionalLight();
        finalColor += CalcPointLights();
        finalColor += CalcSpotLights();

        color = texture(theTexture, texCoord) * finalColor;
    }