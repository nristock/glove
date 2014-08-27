/*
 * IRenderable.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

namespace glove {

class IRenderable {
public:
	IRenderable();
	virtual ~IRenderable();

	virtual void Render() = 0;
};

} /* namespace glove */

#endif /* IRENDERABLE_H_ */
