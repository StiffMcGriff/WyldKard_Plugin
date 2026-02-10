# Mission: WyldKard VST3 Plugin

## Goal
Build a VST3 plugin with semantic search capabilities for audio samples

## Non-Goals
- Real-time collaboration
- Cloud sync
- Mobile support

## User Stories
1. As a producer, I want to search samples by BPM/key
2. As a user, I want to preview waveforms before drag-and-drop
3. As a developer, I want CI/CD for quality assurance

## Data Model
- `samples` table: id, path, bpm, key, genre

## Auth
Session-based (no OAuth required)

## Test Plan
- Unit: Search filters, drag-and-drop handlers
- E2E: Landing → Search → Drop to timeline