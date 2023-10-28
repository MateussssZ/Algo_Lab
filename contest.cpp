#include <iostream>
#include <chrono>
#include <cmath>

void create_first_matrix(int** matrix,int& target,unsigned M,unsigned N){
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            matrix[i][j]=(N/M*i+j)*2;
        }
    }
    target=2*N+1;
}

void create_second_matrix(int** matrix,int& target,unsigned M,unsigned N){
    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            matrix[i][j]=(N/M*i*j)*2;
        }
    }
    target=16*N+1;
    
}

bool second_algorithm(int** matrix,int target,unsigned M,unsigned N){
    int x=M-1,y=0;
    int pointer = matrix[x][y];
    while (pointer!=target && y<N && x>=0){
        pointer=matrix[x][y];
        if (pointer<target){
            y++;
        }
        else{
            x--;
        }
    }
    if (pointer==target){ 
        std::cout << "Target found in " << x << " column and " << y <<" string" << std::endl;
        return true;
    }
    else{
        std::cout <<"No target" << std::endl; 
        return false;
    }
}

int binary_search(int* vector,int l,int r,int target){
    while (l<r){
        int point=(l+r)/2;
        if (vector[point]==target) return point;
        else if (point<target){
            l=point+1;
        }
        else{
            r=point-1;
        }
    }
    return -1;
}

void first_algorithm(int** matrix,int target,unsigned M,unsigned N){
    for (int i =0;i<M;i++){
        int ans = binary_search(matrix[i],0,N-1,target);
        if (ans!=-1){
            std::cout << "Target found in " << i << "column and "<< ans << " string"<<  std::endl;
            return;
        }
    }
    std::cout << "No target\n";
}

int exponential_search(int* vector, int start,int end,int target){
    int check=start;
    while (vector[check]<target && check <= end){
        for (int i =0;i<13;i++){
            check+=pow(2,i);
            if (check>end) break;
            if (vector[check]>target){
                end = check;
                break;
            }
            start=check;
        }
    }
    return binary_search(vector,start,end,target);
    

}

void third_algorithm(int** matrix,unsigned M,unsigned N,int target){
    int x=M-1,y=0;
    while (x>=0){
        if (matrix[x][y]>target){
            x--;
        }
        else{
            y = exponential_search(matrix[x],0,N-1,target);
            if (y==-1){ 
                std::cout << "No target" << std::endl;
                return;
            }
            else{
                std::cout << "Target found in " << x << " column and " << y <<" string" << std::endl;
                return;
            }
        }
    }
}

void check_time(int** matrix,int target,unsigned M,unsigned N,int mode){
    auto start_time = std::chrono::steady_clock::now();
    first_algorithm(matrix,target,M,N);
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    std::cout <<"Time of work of first algo on "<< mode <<" data is equal " <<elapsed_ns.count() << " ns\n";
    start_time = std::chrono::steady_clock::now();
    second_algorithm(matrix,target,M,N);
    end_time = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    std::cout <<"Time of work of second algo on "<< mode <<" data is equal " <<elapsed_ns.count() << " ns\n";
    start_time = std::chrono::steady_clock::now();
    third_algorithm(matrix,M,N,target);
    end_time = std::chrono::steady_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    std::cout <<"Time of work of third algo on "<< mode <<" data is equal " <<elapsed_ns.count() << " ns\n";
}

int main(){
    int x=14;
    while (x>=14 || x<0){
        std::cout << "Введите степень двойки для задания параметра М матрицы(неотрицательное, меньше 14): ";
        std::cin>>x;
    }
    unsigned N =pow(2,13),M=pow(2,x);
    int ** matrix = new int*[M];
    for (int i =0;i<M;i++){
        matrix[i]=new int[N];
    }
    int target;
    for (int x=0;x<14;x++){
        M=pow(2,x);
        std::cout << x << std::endl;
        create_first_matrix(matrix,target,M,N);
        check_time(matrix,target,M,N,1);
        create_second_matrix(matrix,target,M,N);
        check_time(matrix,target,M,N,2);
    }
    for (int i=0;i<pow(2,13);i++){
        delete [] matrix[i];
    }
    delete [] matrix;
    return 0;
}