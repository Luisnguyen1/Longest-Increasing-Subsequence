#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// More efficient O(n log n) solution for LIS
vector<int> LIS(const vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return {};
    
    // piles[i] = index of the smallest element that ends an increasing subsequence of length i+1
    vector<int> piles;
    // prev[i] = previous element's index in the LIS ending at index i
    vector<int> prev(n, -1);
    // pos[i] = position in the LIS that element at index i belongs to
    vector<int> pos(n);
    
    for (int i = 0; i < n; ++i) {
        // Binary search to find the position where nums[i] should go
        int current = nums[i];
        auto it = lower_bound(piles.begin(), piles.end(), current, 
                             [&nums](int idx, int val) { return nums[idx] <= val; });
        
        // If we're at the end, we extend the LIS
        if (it == piles.end()) {
            if (!piles.empty()) {
                prev[i] = piles.back();
            }
            piles.push_back(i);
            pos[i] = piles.size() - 1;
        } 
        // Otherwise, we replace an existing element
        else {
            if (it != piles.begin()) {
                prev[i] = piles[it - piles.begin() - 1];
            }
            *it = i;
            pos[i] = it - piles.begin();
        }
    }
    
    // Reconstruct the LIS
    vector<int> lis;
    if (!piles.empty()) {
        int idx = piles.back();
        while (idx != -1) {
            lis.push_back(idx);
            idx = prev[idx];
        }
        reverse(lis.begin(), lis.end());
    }
    
    return lis;
}

int main() {
    ifstream inFile("LIS.inp");
    ofstream outFile("LIS.out");
    
    int n;
    inFile >> n;
    
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        inFile >> nums[i];
    }
    
    vector<int> lis_indices = LIS(nums);
    
    // Write the length of the LIS
    outFile << lis_indices.size() << endl;
    
    // Write the indices (1-indexed)
    for (int i = 0; i < lis_indices.size(); ++i) {
        outFile << lis_indices[i] + 1; // +1 to convert from 0-indexed to 1-indexed
        if (i < lis_indices.size() - 1) {
            outFile << " ";
        }
    }
    
    inFile.close();
    outFile.close();
    
    return 0;
}
