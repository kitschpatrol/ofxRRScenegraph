/*
 *  BasicScreenObjectEvent.h
 *  BasicScreenObject_Test
 *
 *  Created by Matthias Rohrbach 2 on 10.06.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */

#pragma once

class BasicScreenObject;
class BasicScreenObjectEvent {	
public:
	BasicScreenObject* target;
	void* args;
	
	BasicScreenObjectEvent() {
		target = NULL;
	}
	BasicScreenObjectEvent(BasicScreenObject* _target) {
		target = _target;
	}
};