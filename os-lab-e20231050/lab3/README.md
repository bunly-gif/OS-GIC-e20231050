# Lab 3: Wildcards and Links

**Student:** Vong Bunly  
**Student ID:** e20231050  
**Course:** Operating Systems

## Objectives

- Understand shell wildcard expansion.
- Distinguish between hard links and symbolic links.
- Observe what happens to links when a file is renamed.
- Repair a symbolic link using a relative path.

## Tasks Completed

### Core Tasks

1. **Wildcards:** Practiced `*`, `?`, and quoted wildcard patterns.
2. **Hard Links:** Created a hard link and verified that it shares the same inode as the original file.
3. **Symbolic Links:** Created a symbolic link and observed how it behaves after renaming its target.
4. **File Replacement:** Created a new file using the original filename and verified that the symbolic link followed the new file.
5. **Link Repair:** Recreated the symbolic link with a relative target pointing to `river-backup.txt`.

### Plus Task

Practiced character classes `[12]` and `[!1]` to match filenames using more specific wildcard patterns.

## Evidence

| File | Description |
|---|---|
| `wildcards.txt` | Core wildcard expansion results |
| `links.txt` | Link behavior before rename, after rename, and after repair |
| `replacement.txt` | New file and link behavior after filename reuse |
| `plus.txt` | Additional wildcard pattern results |

## Result

All five core milestones passed using `oslab check lab3`.

The Live Checkpoint is pending instructor availability.
