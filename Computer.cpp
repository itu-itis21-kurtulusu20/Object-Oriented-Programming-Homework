#include <string>
#include <iostream>
#include "Computer.h"
/* Constructor */
Computer::Computer(){ //constructor for computer
        std::cout << "Computer is ready"<< std::endl;
        attachedCPU = nullptr;
        attachedGPU = nullptr;
}
void Computer::execute(const std::string operation) const{ // execute method for computer. we will first check will the gpu or the cpu do the job by booleans
    bool cpu_check = false;                                // and call the appropiate execute method.
    bool gpu_check = false;    
    if(operation == "subtract" || operation == "add"  || operation == "multiply" ){
        cpu_check = true; // this 3 operations belong to cpu
    }
    else if(operation == "render" || operation == "trainModel" ){
        gpu_check = true;// this 2 operations belong to gpu
}

    if(cpu_check){
        std::cout << this->attachedCPU->execute(operation) << std::endl;
    }
    else if(gpu_check){
        std::cout << this->attachedGPU->execute(operation) <<std::endl;
    }
}


CPU::CPU(int numPerCores) //constructor for cpu (it will create a new ALU)
{
    this->alu = new ALU(numPerCores);
    std::cout << "CPU is ready"<< std::endl;
}

CPU::~CPU(){      // destructor that deletes the alu we created.
    delete alu;
}

int CPU::execute(const std::string operation) const{ // execute method for 3 operations of CPU.
    int number1,number2;
    std::cout << "Enter two integers"<< std::endl;
    std::cin >> number1 >> number2 ;
    if(operation == "subtract"){
       return alu->substract(number1,number2);
    }
    else if(operation == "add"){
        return alu->add(number1,number2);
    }
    else if(operation == "multiply"){
        return alu->multiply(number1,number2);
    }
    return 0;
}
ALU::ALU(int numPerCores){ // constructor for ALU. it only has one attribute.
    this->numPerCores=numPerCores;
    std::cout << "ALU is ready"<< std::endl;
}

int ALU::add(int x1,int x2){
    return x1 + x2;
}
int ALU::substract(int x1,int x2){
    return x1 - x2;
}
int ALU::multiply(int x1,int x2){
    return x1 * x2;
}


GPU::GPU(int numCores)         // constructor of GPU that will create a new CUDA. 
{
    this->cuda = new CUDA(numCores);
    std::cout << "GPU is ready"<< std::endl;
}

GPU::~GPU(){          // deleting the cuda we created.
    delete cuda;
}
std::string GPU::execute(const std::string operation) const{     // execute method for the 2 operations of GPU.
    if(operation == "render"){
        return cuda->render();
    }
    else if(operation == "trainModel"){
        return cuda->trainModel();
    }
    return 0;
}

CUDA::CUDA(int numCores){           //CUDA constructor (only one attribute.)
    this->numCores = numCores;
    std::cout << "CUDA is ready"<< std::endl;
}
//METHODS OF CUDA:
std::string CUDA::render(){
    return "Video is rendered";
}
std::string CUDA::trainModel(){
    return "AI Model is trained";
}



// this method will check if the cpu is attached or not, we will use that in the operator+
bool attachment_check_cpu(Computer& comp){
    if(!comp.getCpu()){
        return false;
    }
    else{
        return true;
    }
}
void operator+(Computer& comp,CPU& cpu) {
    if(!attachment_check_cpu(comp)){
        comp.setCpu(cpu); // if we get false from tha attachment_check we will attach the cpu.
        std::cout << "CPU is attached"<< std::endl;  
    }
    else
        std::cout << "There is already a CPU"<< std::endl;
}

// this method will check if the gpu is attached or not, if its not attached it it will attach it.
void operator+(Computer& comp,GPU& gpu)  {
    if(!comp.getGpu()){
        comp.setGpu(gpu);
        std::cout << "GPU is attached"<< std::endl;
    }
    else
        std::cout << "There is already a GPU"<< std::endl;
}
