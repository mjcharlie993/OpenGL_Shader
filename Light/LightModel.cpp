const char * GetEarthVert()
{
	const char* EarthVert =
	{
		"#version 330 core\n"
		"uniform mat4 osg_ModelViewProjectionMatrix;\n"		
		"uniform mat3 osg_NormalMatrix;\n"
		"uniform mat4 osg_ViewMatrix;\n"
		"in vec3 osg_Normal;\n"										
		"in vec4 osg_Vertex;\n"								
		"in vec4 osg_MultiTexCoord0;\n"						
		"out vec4 vs_tex_coord;\n"	
		"out vec3 EyePosition;\n"
		"out vec3 ecNormal;\n"	
		"void main()\n"
		"{\n"
		"   ecNormal = normalize( osg_NormalMatrix * osg_Normal ); \n"
		"	gl_Position = osg_ModelViewProjectionMatrix * osg_Vertex;\n"
		"	vs_tex_coord = osg_MultiTexCoord0;\n"
		"	vec3 EyePosition = vec3(-gl_Position.xyz);\n"
		"}\n"
	};

	return EarthVert;
}


const char* GetEarthFrag()
{
	const char* EarthFrag = 
	{
		"#version 330 core\n"
		"uniform vec4 Color;\n"
		"uniform mat4 osg_ViewMatrix;\n"
		"uniform sampler2D texMap;\n"
		"uniform vec3 sunLightParam;\n"
		"uniform vec3 EyeWorldPos;\n"
		"in vec4 vs_tex_coord;\n"
		"in vec3 ecNormal;\n"
		"in vec4 osg_Vertex;\n"	
		"in vec3 EyePosition;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	vec4 Color = vec4(1.0,1.0,1.0,1.0);\n"
		"   vec4 AmbientColor = Color * 0.5;\n"
		"   vec4 li = osg_ViewMatrix * vec4(sunLightParam,0.0);\n"
		"   vec3 L = normalize(li.xyz);\n"
		"	vec3 N = ecNormal;\n"
		"	vec3 H = normalize(L + EyePosition);\n"
		"	float df = max(dot(N,L),0.0);\n"
		"	float sf = max(dot(N,H),0.0);\n"
		"	sf = pow(sf,32);\n"
		"	vec4 DiffuseColor = Color * 0.8 * df;\n"
		"	vec4 SpecularColor = Color * 0.6 * sf;\n"
		"	FragColor = texture(texMap,vs_tex_coord.st) * ( AmbientColor + DiffuseColor + SpecularColor);\n"
		"}\n"
	};

	return EarthFrag;
}