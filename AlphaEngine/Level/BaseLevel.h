#pragma once

namespace GSM
{
	class BaseLevel
	{
		//Pure Abstract - Can not be instatiated
		//Others will inherit from me, I am just an Interface
		
	public:
		//Init
		virtual void Init() = 0;
		//Update
		virtual void Update() = 0;
		//Exit
		virtual void Exit() = 0;

		//Other functionality
		//Private data...
	};
}