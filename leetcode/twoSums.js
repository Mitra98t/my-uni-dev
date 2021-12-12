/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
var twoSum = function (nums, target) {
    for (const n in nums) {
        for (const n1 in nums) {
            if (n != n1 && nums[n] + nums[n1] == target) {
                return [n, n1]
            }
        }
    }
    return []
};


let nums = [2, 7, 11, 15]
let target = 9

console.time('doSomething')

console.log(twoSum(nums, target))

console.timeEnd('doSomething')
