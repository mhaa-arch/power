# Using Power Management across targets

The only project dependency is the matching `power-contract`. Keep its API revision aligned with this Core.

Portable callers can request a category or use the prefix result from a clock batch. They still need a target mapping for logical IDs and a policy for wake sources, shared gates and partial changes. Deep sleep may restart the target rather than return.

This repository's host simulations and shared API compile/link checks provide source-level evidence. Target timing and physical behavior require hardware validation.
