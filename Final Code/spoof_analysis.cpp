#include "spoof_analysis.h"
#include "spoof_utils.h"

void getDomains(string &realDomain, string &testDomain) {
    cout << "Enter trusted domain: ";
    cin >> realDomain;
    cout << "Enter suspicious domain: ";
    cin >> testDomain;
}

SpoofResult analyzeSpoof(const string &realDomain, const string &testDomain) {
    SpoofResult r;

    string cleanReal = normalizeDomain(realDomain);
    string cleanTest = normalizeDomain(testDomain);

    r.similarity = compareDomains(cleanReal, cleanTest);

    if (r.similarity >= 85)
        r.verdict = "HIGH RISK — Visually looks like the real domain.";
    else if (r.similarity >= 60)
        r.verdict = "MEDIUM RISK — Possible spoof.";
    else
        r.verdict = "LOW RISK — Probably safe.";

    return r;
}

void showResult(const SpoofResult &r, const string &realDomain, const string &testDomain) {
    cout << "\n--- Visual Spoof Detection Report ---\n";
    cout << "Trusted Domain:    " << realDomain << "\n";
    cout << "Suspicious Domain: " << testDomain << "\n";
    cout << "Similarity:        " << r.similarity << "%\n";
    cout << "Verdict:           " << r.verdict << "\n";
}
