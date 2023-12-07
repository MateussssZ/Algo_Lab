#include <iostream>
#include <chrono>
#include <cmath>

void create_first_matrix(int** matrix,int& target,unsigned M,unsigned N){
    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            matrix[i][j]=(N/M*i+j)*2;
        }
    }
    target=2*N+1;
}

void create_second_matrix(int** matrix,int& target,unsigned M,unsigned N){
    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            matrix[i][j]=(N/M*i*j)*2;
        }
    }
    target=16*N+1;
    
}

bool second_algorithm(int** matrix,int target,unsigned M,unsigned N){
    int x=0,y=M-1;
    int pointer = matrix[x][y];
    while (pointer!=target && x<N && y>=0){
        pointer=matrix[x][y];
        if (pointer<target){
            x++;
        }
        else{
            y--;
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

int bin_search(int** matrix,int y,int left,int right,int target){
    while (left<right){
        int mid=(left+right)/2;
        if (matrix[mid][y]==target) return mid;
        else if (mid<target){
            left=mid+1;
        }
        else{
            right=mid-1;
        }
    }
    return -1;
}

void first_algorithm(int** matrix,int target,unsigned M,unsigned N){
    for (int i =0;i<M;i++){
        int ans = bin_search(matrix,i,0,N-1,target);
        if (ans!=-1){
            std::cout << "Target found in " << i << "column and "<< ans << " string"<<  std::endl;
            return;
        }
    }
    std::cout << "No target\n";
}

int exponential_search(int** matrix,int y,int end,int target){
    int k=1,x=0;
    while (matrix[x][y]<target && x <= end){
        x+=k;
        k*=2;
        if (x>end) return bin_search(matrix,y,x=x-(k/2),end,target);
        else{
            if (matrix[x][y]>target){
            return bin_search(matrix,y,x=x-(k/2),x-1,target);
            }
        }
    }
    

}

void third_algorithm(int** matrix,unsigned M,unsigned N,int target){
    int y=M-1,x=0;
    while (y>=0){
        if (matrix[x][y]>target){
            y--;
        }
        else{
            x = exponential_search(matrix,y,N-1,target);
            if (x==-1){ 
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
    int x=-1;
    while (x>=14 || x<0){
        std::cout << "Введите степень двойки для задания параметра М матрицы(неотрицательное, меньше 14): ";
        std::cin>>x;
    }
    unsigned N =pow(2,13),M=pow(2,x);
    int ** matrix = new int*[N];
    for (int i =0;i<N;i++){
        matrix[i]=new int[M];
    }
    int target;
    create_first_matrix(matrix,target,M,N);
    check_time(matrix,target,M,N,1);
    create_second_matrix(matrix,target,M,N);
    check_time(matrix,target,M,N,2);
    for (int i=0;i<N;i++){
        delete [] matrix[i];
    }
    delete [] matrix;
    return 0;
}
