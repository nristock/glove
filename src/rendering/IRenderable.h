/*
 * IRenderable.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

namespace glove {
namespace gl {
namespace rendering {

class IRenderable {
public:
	IRenderable();
	virtual ~IRenderable();

	virtual void Render() = 0;
};

} /* namespace rendering */
} /* namespace gl */
} /* namespace glove */

#endif /* IRENDERABLE_H_ */
