#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>

using v = std::vector<int>;

// ===== std::sort wrapper =====
void std_sort(v& a) {
    std::sort(a.begin(), a.end());
}

// ===== benchmark wrapper =====
void benchmark(const char* name, void (*sort_func)(v&), int n)
{
    v a(n);

    // 固定随机种子，保证可复现
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 1'000'000);

    for (int i = 0; i < n; ++i) {
        a[i] = dist(gen);
    }

    auto start = std::chrono::high_resolution_clock::now();
    sort_func(a);
    auto end = std::chrono::high_resolution_clock::now();

    bool ok = std::is_sorted(a.begin(), a.end());

    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << name << '\n';
    std::cout << "  n = " << n << '\n';
    std::cout << "  time = " << elapsed.count() << " ms\n";
    std::cout << "  sorted = " << (ok ? "true" : "false") << "\n\n";
}

// ===== the sorts below : small -> big =====

void bubble_sort(v& a)
{
    std::size_t n = a.size();
    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = 0; j + 1 < n - i; ++j)
            if (a[j] > a[j + 1])
                std::swap(a[j], a[j + 1]);
    }
}

void insert_sort(v& a)
{
    std::size_t n = a.size();
    for (std::size_t i = 1; i < n; ++i)
    {
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && a[j + 1] < a[j])
        {
            std::swap(a[j + 1], a[j]);
            --j;
        }
    }
}

// we use gap = gap / 2
void shell_sort(v& a)
{
    int n = static_cast<int>(a.size());
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; ++i)
        {
            int temp = a[i];
            int j = i;
            while (j >= gap && a[j - gap] > temp)
            {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
    }
}

void shell_sort_knuth(v& a)
{
    int n = static_cast<int>(a.size());
    
    // 1. 计算初始 gap (Knuth 序列: 1, 4, 13, 40...)
    int gap = 1;
    while (gap < n / 3) {
        gap = 3 * gap + 1;
    }

    while (gap >= 1)
    {
        for (int i = gap; i < n; ++i)
        {
            int temp = a[i];
            int j = i;
            while (j >= gap && a[j - gap] > temp)
            {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
        // 2. 缩小 gap
        gap = gap / 3; 
    }
}

int partition(v& a, int left, int right)
{
    int pivot = a[left], pivotpos = left;
    for(int i = left + 1; i < right; i++)
    {
        if(a[i] < pivot)
        {
            pivotpos++;
            std::swap(a[i], a[pivotpos]);
        }
    }
    a[left] = a[pivotpos];
    a[pivotpos] = pivot;
    
    return pivotpos;
}

void quick_sort_handler(v& a, int left, int right)
{
    if(left >= right)
        return;

    int pivotpos = partition(a, left, right);
    quick_sort_handler(a, left, pivotpos);
    quick_sort_handler(a, pivotpos + 1, right);
}

void quick_sort(v& a)
{
    if(a.empty())
        return ;
    
    quick_sort_handler(a, 0, a.size());
}

void select_sort(v& a)
{
    int n = a.size();
    for(int i = 0; i < n; i++)
    {
        int min = INT_MAX, minindex = i;
        for(int j = i; j < n; j++)
        {
            if(a[j] < min)
            {
                min = a[j];
                minindex = j;
            }
        }
        std::swap(a[i], a[minindex]);
    }
}

void siftdown(v& a, int index, int size)
{
    int max = index;
    while(1)
    {
        int lchild = index * 2 + 1;
        int rchild = index * 2 + 2;
        if(lchild < size && a[lchild] > a[max])
            max = lchild;
        if(rchild < size && a[rchild] > a[max])
            max = rchild;
        if(max != index)
        {
            std::swap(a[max], a[index]);
            index = max;
        }
        else
            break;
    }
}

void heap_sort(v& a)
{
    int n = a.size();
    for(int i = n / 2 - 1; i >= 0; i--)
    {
        siftdown(a, i, n);
    }
    for(int i = n - 1; i >= 0; i--)
    {
        std::swap(a[0], a[i]);
        siftdown(a, 0, i);
    }
}

void merge(v& a1, v& a2, int left, int mid, int right)
{
    for(int i = left; i <= right; i++)
        a2[i] = a1[i];
    int s1 = left, s2 = mid + 1, t = left;
    while(s1 <= mid && s2 <= right)
        if(a2[s1] < a2[s2])
            a1[t++] = a2[s1++];
        else
            a1[t++] = a2[s2++];
    while(s1 <= mid)
        a1[t++] = a2[s1++];
    while(s2 <= right)
        a1[t++] = a2[s2++];
}

void merge_sort_handler(v& a1, v& a2, int left, int right)
{
    if(left >= right)
        return;
    
    int mid = (left + right) / 2;
    merge_sort_handler(a1, a2, left, mid);
    merge_sort_handler(a1, a2, mid + 1, right);
    merge(a1, a2, left, mid, right);
}

void merge_sort(v& a)
{
    int n = a.size();
    v b(n);
    merge_sort_handler(a, b, 0, n - 1);
}



