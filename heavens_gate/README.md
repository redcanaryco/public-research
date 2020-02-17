# Heaven's Gate for Linux


Heaven’s Gate was originally published as an attacker technique for Windows. This technique allowed malicious software to evade endpoint security products by invoking 64-bit code in 32-bit processes, effectively bypassing user-mode hooks. This technique has since been mitigated in Windows 10+ through Control Flow Guard (CFG).

Red Canary has been successful in reproducing a variation of this technique for Linux.

PoC's: https://github.com/redcanaryco/public-research/tree/master/heavens_gate/src
