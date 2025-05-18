#define LIST_SIZE 10

class GoalTracker{
public:

	int m_ledPin;
	int m_resistorPin;
	int valueList[LIST_SIZE];
	int m_goalThreshold;
	bool isBallPresent = false;
	int count = 0;
	GoalTracker(){
		for(int i = 0; i < LIST_SIZE; i++){
			valueList[i] = 255;
		}
	};



	void Init(int ledPin, int resistorPin, int goalThreshold);

	bool checkNewPoint();

	double getSensorValue(){
		double sum = 0;
		for( auto i : valueList){
		  sum += i;
		}
		return sum / LIST_SIZE;
	  }
};