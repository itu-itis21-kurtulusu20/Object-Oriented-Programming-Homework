#include <string>
#include <iostream>
class ALU 
{
public:
    ALU(int);  // constructor (we have only attribute numPerCores.)
    int add(int,int); // method for adding
    int substract(int,int); // method for substracting
    int multiply(int,int); // method for multiplying
private:
    int numPerCores;

};
class CPU
{
public:
    CPU(int);
    // this attribute is numPerCores at it will sent to ALU object for operations.
    ~CPU(); 
    //destructor
    int execute(const std::string) const;

private:
    ALU *alu;

};

class CUDA
{
public: 
    CUDA(int); // constructor (only one attribute numCores)
    std::string trainModel();
    std::string render();
private:
    int numCores;

};

class GPU
{
public:
    GPU(int);
      // this attribute is numCores at it will sent to CUDA for operations.
    ~GPU();
    // destructor for cuda

    std::string execute(const std::string)const; 
        // Operation will be executed on CUDA and result will be returned.
private:
    CUDA *cuda;

};





class Computer   
{
    friend void operator+(Computer&,CPU&);
    //operator+ for cpu
    friend void operator+(Computer&,GPU&);
    //operator+ for gpu
public:
    Computer();
    // will tell the user that computer is ready and attach cpu and gpu to null.
    void execute(const std::string) const;
    // attachments will be done in here with setters and getters.
    CPU* getCpu() {return attachedCPU;}
    void setCpu(CPU& cpu) {attachedCPU = &cpu;}
    GPU* getGpu() {return attachedGPU;}
    void setGpu(GPU& gpu) {attachedGPU = &gpu;} 
private:
    CPU *attachedCPU{NULL};
    GPU *attachedGPU{NULL};
};



