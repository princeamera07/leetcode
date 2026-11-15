
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> positions;
        int index = 1;

        ListNode* prev = head;
        ListNode* curr = head->next;

        while (curr && curr->next) {
            if ((curr->val > prev->val && curr->val > curr->next->val) ||
                (curr->val < prev->val && curr->val < curr->next->val)) {
                positions.push_back(index);
            }

            prev = curr;
            curr = curr->next;
            index++;
        }

        if (positions.size() < 2) return {-1, -1};

        int minDist = INT_MAX;

        for (int i = 1; i < positions.size(); i++) {
            minDist = min(minDist, positions[i] - positions[i - 1]);
        }

        int maxDist = positions.back() - positions.front();

        return {minDist, maxDist};
    }
};
