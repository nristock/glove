/*
 * IRenderable.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

namespace glove {

struct FrameData;

class IRenderable {
public:
	IRenderable();
	virtual ~IRenderable();

	virtual void Render(FrameData& frameData) = 0;
};

} /* namespace glove */

#endif /* IRENDERABLE_H_ */
