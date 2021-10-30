using namespace vex;

void timeFwdRev(int motorPower, float sec);
void moveFwdRev(double motorPower, int Degrees);
void TurnInPlace(float Deg, double slowDown, int minSpeed);
void intakeFunc(float sec, std::string type);
void indexerFunc(float sec, std::string type);


void StrafeXY(double x, double y, int speed, double decel);
void SetVelocityTheta(double th, double speed, std::string state);