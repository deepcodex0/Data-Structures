/**
 * LeetCode Q.05 - "Longest Palindromic Substring"
 * Link: https://leetcode.com/problems/longest-palindromic-substring/
 * Twitter Article with detailed explanation:
 * 
 * Problem Statement: Given a string s, return the longest palindromic substring in s.
 * Example 1:
 * Input: s = "babad"
 * Output: "bab"
 * Explanation: "aba" is also a valid answer.
 * 
 * Example 2:
 * Input: s = "cbbd"
 * Output: "bb"
 * 
 * Constraints:
 * 1 <= s.length <= 1000
 * s consist of only digits and English letters.
 */

// Brute force 
function longestPalindromeSubstring(s) {
    
    if (s.length < 2) return s;
    
    let longest = '';
    
    // Function to check if a string is a palindrome
     const isValidPalindrome = (s) => {
        let left = 0, right = s.length - 1;

        while(left < right) {
            if(s[left] !== s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
    
    // Check all possible substrings
    for (let i = 0; i < s.length; i++) {
        for (let j = i + 1; j <= s.length; j++) {
            let substr = s.slice(i, j);
            if (isValidPalindrome(substr) && substr.length > longest.length) {
                longest = substr;
            }
        }
    }
    
    return longest;
}