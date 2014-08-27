/*
 * GloveObject.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef GLOVEOBJECT_H_
#define GLOVEOBJECT_H_

#include "../log/log.h"

#define OLOG(lvl_) LOG(this->logger, lvl_)

namespace glove {

class GloveObject {
public:
	GloveObject();
	virtual ~GloveObject();

protected:
	logging::GloveLogger logger;
};

} /* namespace glove */

#endif /* GLOVEOBJECT_H_ */
