#include "Material.h"

#include <glm/gtc/type_ptr.hpp>

#include "core/GloveException.h"
#include "shader/ShaderProgram.h"

namespace glove {
	
Material::Material(ShaderProgramPointer shader) : shader(shader) {

}

Material::~Material() {
	
}

void Material::SetMaterialAttribute(MappedMaterialAttribute mappedAttribute, float& value) {
	try {
		GLuint attributeIndex = shader->GetMaterialAttributePosition(mappedAttribute);
		shader->Enable();
		glUniform1f(attributeIndex, value);
	}
	catch (const GloveException& ex) {
		OLOG(error, "Failed to set material attribute: " << ex.what());
	}
}

void Material::SetMaterialAttribute(MappedMaterialAttribute mappedAttribute, glm::vec3& value) {
	try {
		GLuint attributeIndex = shader->GetMaterialAttributePosition(mappedAttribute);
		shader->Enable();
		glUniform3fv(attributeIndex, 1, glm::value_ptr(value));
	}
	catch (const GloveException& ex) {
		OLOG(error, "Failed to set material attribute: " << ex.what());
	}

}

void Material::SetMaterialAttribute(MappedMaterialAttribute mappedAttribute, glm::vec4& value) {
	try {
		GLuint attributeIndex = shader->GetMaterialAttributePosition(mappedAttribute);
		shader->Enable();
		glUniform4fv(attributeIndex, 1, glm::value_ptr(value));
	}
	catch (const GloveException& ex) {
		OLOG(error, "Failed to set material attribute: " << ex.what());
	}

}

void Material::SetMaterialAttribute(MappedMaterialAttribute mappedAttribute, glm::mat4x4& value) {
	try {
		GLuint attributeIndex = shader->GetMaterialAttributePosition(mappedAttribute);
		shader->Enable();
		glUniformMatrix4fv(attributeIndex, 1, false, glm::value_ptr(value));
	}
	catch (const GloveException& ex) {
		OLOG(error, "Failed to set material attribute: " << ex.what());
	}

}

void Material::PySetMaterialAttributeF(MappedMaterialAttribute mappedAttribute, float& value) {
	SetMaterialAttribute(mappedAttribute, value);
}
void Material::PySetMaterialAttributeV3(MappedMaterialAttribute mappedAttribute, glm::vec3& value) {
	SetMaterialAttribute(mappedAttribute, value);
}
void Material::PySetMaterialAttributeV4(MappedMaterialAttribute mappedAttribute, glm::vec4& value) {
	SetMaterialAttribute(mappedAttribute, value);
}
void Material::PySetMaterialAttributeMat4(MappedMaterialAttribute mappedAttribute, glm::mat4x4& value) {
	SetMaterialAttribute(mappedAttribute, value);
}

void Material::Enable() const {
	shader->Enable();
}

void Material::Disable() const {
	shader->Disable();
}

} // namespace glove