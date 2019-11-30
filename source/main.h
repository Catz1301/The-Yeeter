
/* Define functions */
int main();

void doReset();

/* Define 1 lonely flag */
bool debug = false;

/* Define sf::Colors */
sf::Color invisible = sf::Color(0, 0, 0, 0);
sf::Color visible = sf::Color(255, 255, 255, 255);

/* Define a bunch of flags */

bool jump = false;				// Defines whether we're jumping or not
bool reset = false;				// Defines the reset flag 
bool failed = false;			// Defines whether we've failed or not
bool goingUp = false;			// Defines whether we're in the process of going up while jumping or not
bool firstRun = true;			// This should be obvious
bool firstTime = true;			// I don't think this is used
bool goingDown = false;			// Defines whether we're in the process of going down while jumping or not
bool movingLeft = false;		// Defines whether the player is moving left or not
bool movingRight = false;		// Defines whether the player is moving right or not
bool restrictDisp = false;		// I don't think this is used
bool objYeetMoving = false;		// Defines whether or not objYeet should be moving
bool objYeetMoving1 = false;	// Defines whether or not objYeet1 should be moving
bool objYeetMoving2 = false;	// Defines whether or not objYeet2 should be moving
bool objYeetHittable = false;	// Defines whether or not objYeet is hittable
bool objYeet1Hittable = false;	// Defines whether or not objYeet1 is hittable
bool objYeet2Hittable = false;	// Defines whether or not objYeet2 is hittable
bool resetFailed = false;

bool objYeet_out = false;
bool objYeet1_out = false;
bool objYeet2_out = false;
bool animEnabled = false;

const int ground = 452;
double animSize;


/* Preprocessor definitions */

#ifndef whenBig			// If 'whenBig' is not defined, then 
#define whenBig 542.5	// define it with a value of 542.5
#endif // !whenBig		// End if statment for whenBig

#ifndef whenNormal		// If 'whenNormal' is not defined, then 
#define whenNormal 575	// define it with a value of 575
#endif // !whenNormal	// End if statment for whenNormal