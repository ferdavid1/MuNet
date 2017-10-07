#include <neuralDuino.h>
#define NUM_SET 4
#define NUM_SYN 3
#define NUM_OUT_NODES 1 //single layer perceptron, bc 1 total neuron required

neuron node1,node2,node3,node4;

float sigmoidact(float in,byte isDerivative){
  return isDerivative==HIGH?sigmoidDerivative(in):sigmoid(in);
  }

void setupNN() {

  node1.begin(3); //input node, parameter is number of synapses
  node2.begin(3); //input node
  node3.begin(3); //output node
  node4.begin(0); //bias node

  node1.setActivationFn(&sigmoidact);
  node2.setActivationFn(&sigmoidact);
  node3.setActivationFn(&sigmoidact);
  node4.setActivationFn(&sigmoidact);

  // this part means just input + input + bias are connected to 3, the output node.  
  node3.connectInput(&node1);
  node3.connectInput(&node2);
  node3.connectInput(&node4);

  node4.setOutput(1); //set bias node to output of 1
  Serial.println("Connected");
}

 //these are normalized inputs
float input1[NUM_SET][NUM_SYN] = {
           //{binary input, dummy input, bias for input nodes}
                                {0, 0,1},
                                {1, 0,1},
                                {0, 0,1},
                                {1, 0,1},
                                };
float input2[NUM_SET][NUM_SYN] = {
                                {0, 0,1},
                                {0, 0,1},
                                {1, 0,1},
                                {1, 0,1},
                                };


void learn(){
//output can never be negative since 
//it is the output of a sigmoid function
  float output[NUM_SET]  ={1,2,3,4};
  for(unsigned int i=0;i<500;i++){
    for(byte k=0;k<NUM_SET;k++){
        //send the input values to the input nodes
        //the input array is of finite length configurable by library header parameter NUM_SYN
        node1.setInput(input1[k]);
        node2.setInput(input2[k]);
              //now ask for the output from the output nodes one by one 
              //set the desired output in the output nodes only
              //call backpropagate to bkprpg8 to only 1 level behind the calling nodes
        node3.getOutput();
        node3.setDesiredOutput(output[k]);
        node3.backpropagate();
//call adjustWeights for all nodes after backrprp8n is done for every node
        node3.adjWeights();
        node3.printWeights();
        node2.adjWeights();
        node2.printWeights();
        node1.adjWeights();
        node1.printWeights();
        
        //instead of using the provided AdjustWeights function, 
        
    }
  } 
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupNN();
  //print the inital weights if reqd
  node1.printWeights();
  node2.printWeights();
  node3.printWeights();
  delay(500);
  learn();
  Serial.println("learn done");
  Serial.flush();
  Serial.println(millis());
  node1.printWeights();
  node2.printWeights();
  node3.printWeights();

  //TESTING the learned model
 node1.setInput(input1[0]);
 node2.setInput(input2[0]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node3.getOutput());
 Serial.println("----");
 
 node1.setInput(input1[1]);
 node2.setInput(input2[1]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node3.getOutput());
 Serial.println("----");

 node1.setInput(input1[2]);
 node2.setInput(input2[2]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node3.getOutput());
 Serial.println("----");

 node1.setInput(input1[3]);
 node2.setInput(input2[3]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node3.getOutput());
 Serial.println("----");

  
}

void loop() {
  delay(2000);
}


