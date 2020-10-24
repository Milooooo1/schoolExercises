#include "melody.hpp"

void melody::play( note_player & p){
	p.play( note{ note::659,	note::250000 	} );
	p.play( note{ note::622,	note::250000 	} );
	p.play( note{ note::659,	note::250000 	} );
	p.play( note{ note::622,	note::250000 	} );
	p.play( note{ note::659,	note::250000 	} );
	p.play( note{ note::494,	note::250000 	} );
	p.play( note{ note::587,	note::250000 	} );
	p.play( note{ note::523,	note::250000 	} );
	p.play( note{ note::440,	note::500000 	} );
	p.play( note{ note::698,	note::357142 	} );
	p.play( note{ note::1046,	note::178571 	} );
	p.play( note{ note::987,	note::89285 	} );
	p.play( note{ note::1046,	note::89285 	} );
	p.play( note{ note::987,	note::89285 	} );
	p.play( note{ note::1046,	note::89285 	} );
	p.play( note{ note::987,	note::178571 	} );
	p.play( note{ note::1046,	note::178571 	} );
	p.play( note{ note::830,	note::357142 	} );
	p.play( note{ note::698,	note::357142 	} );
	p.play( note{ note::698,	note::178571 	} );
	p.play( note{ note::830,	note::178571 	} );
	p.play( note{ note::1046,	note::178571 	} );
	p.play( note{ note::1108,	note::357142 	} );
	p.play( note{ note::830,	note::357142 	} );
	p.play( note{ note::1108,	note::357142 	} );
	p.play( note{ note::1244,	note::357142 	} );
	p.play( note{ note::1046,	note::178571 	} );
	p.play( note{ note::1108,	note::178571 	} );
	p.play( note{ note::1046,	note::178571 	} );
	p.play( note{ note::1108,	note::178571 	} );
	p.play( note{ note::1046,	note::714285 	} );
}
