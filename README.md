# Wabbit

A wabbit (fork-bomb style self replicator) for Windows, in C. Saw one in a video,
got curious, ported the idea. It spawns copies of itself with random names and
keeps going until the machine chokes.

This is not a graphics experiment. It is destructive by design.

## Warning

Run this only in a VM or a throwaway lab box. It will make a machine unusable.
Do not run it on anything you care about.

## Build

```bash
gcc wabbit.c -o wabbit
```

There is a prebuilt one in `BINARY`. Same warning applies, more so.

## License

MIT
