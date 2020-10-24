#include "melody.hpp"
#include "note.hpp"

void melody::play( note_player & p){
	p.play( note{ 659,	250000 	} );
	p.play( note{ 622,	250000 	} );
	p.play( note{ 659,	250000 	} );
	p.play( note{ 622,	250000 	} );
	p.play( note{ 659,	250000 	} );
	p.play( note{ 494,	250000 	} );
	p.play( note{ 587,	250000 	} );
	p.play( note{ 523,	250000 	} );
	p.play( note{ 440,	500000 	} );
	p.play( note{ 698,	357142 	} );
	p.play( note{ 1046,	178571 	} );
	p.play( note{ 987,	89285 	} );
	p.play( note{ 1046,	89285 	} );
	p.play( note{ 987,	89285 	} );
	p.play( note{ 1046,	89285 	} );
	p.play( note{ 987,	178571 	} );
	p.play( note{ 1046,	178571 	} );
	p.play( note{ 830,	357142 	} );
	p.play( note{ 698,	357142 	} );
	p.play( note{ 698,	178571 	} );
	p.play( note{ 830,	178571 	} );
	p.play( note{ 1046,	178571 	} );
	p.play( note{ 1108,	357142 	} );
	p.play( note{ 830,	357142 	} );
	p.play( note{ 1108,	357142 	} );
	p.play( note{ 1244,	357142 	} );
	p.play( note{ 1046,	178571 	} );
	p.play( note{ 1108,	178571 	} );
	p.play( note{ 1046,	178571 	} );
	p.play( note{ 1108,	178571 	} );
	p.play( note{ 1046,	714285 	} );
}
