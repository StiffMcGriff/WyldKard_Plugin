import { useState } from 'react';

interface Sample {
  id: number;
  name: string;
  bpm: number;
  key: string;
  genre: string;
  duration: string;
  waveform: number[];
}

const mockSamples: Sample[] = [
  { id: 1, name: "Dark Synth Bass", bpm: 128, key: "A minor", genre: "Electronic", duration: "0:08", waveform: [0.2, 0.5, 0.8, 0.6, 0.9, 0.7, 0.4, 0.3, 0.6, 0.8, 0.5, 0.3] },
  { id: 2, name: "Crispy Hi-Hat Loop", bpm: 140, key: "C major", genre: "Drum & Bass", duration: "0:04", waveform: [0.4, 0.4, 0.5, 0.4, 0.4, 0.5, 0.4, 0.4, 0.5, 0.4, 0.4, 0.5] },
  { id: 3, name: "Ambient Pad Texture", bpm: 90, key: "D minor", genre: "Ambient", duration: "0:16", waveform: [0.1, 0.2, 0.4, 0.6, 0.7, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2] },
  { id: 4, name: "Punchy Kick", bpm: 128, key: "C major", genre: "House", duration: "0:01", waveform: [0.9, 0.7, 0.5, 0.3, 0.2, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1] },
  { id: 5, name: "Vocal Chop", bpm: 120, key: "G major", genre: "Pop", duration: "0:02", waveform: [0.3, 0.6, 0.8, 0.9, 0.7, 0.5, 0.6, 0.7, 0.5, 0.3, 0.2, 0.1] },
  { id: 6, name: "Melodic Pluck", bpm: 128, key: "A minor", genre: "Electronic", duration: "0:06", waveform: [0.5, 0.7, 0.4, 0.6, 0.8, 0.5, 0.7, 0.6, 0.4, 0.5, 0.3, 0.2] },
];

export function SampleSearchDemo() {
  const [searchQuery, setSearchQuery] = useState('');
  const [selectedBpm, setSelectedBpm] = useState('');
  const [selectedKey, setSelectedKey] = useState('');
  const [selectedGenre, setSelectedGenre] = useState('');
  const [draggedSample, setDraggedSample] = useState<Sample | null>(null);

  const filteredSamples = mockSamples.filter(sample => {
    const matchesSearch = sample.name.toLowerCase().includes(searchQuery.toLowerCase()) ||
                         sample.genre.toLowerCase().includes(searchQuery.toLowerCase());
    const matchesBpm = !selectedBpm || sample.bpm.toString() === selectedBpm;
    const matchesKey = !selectedKey || sample.key === selectedKey;
    const matchesGenre = !selectedGenre || sample.genre === selectedGenre;
    
    return matchesSearch && matchesBpm && matchesKey && matchesGenre;
  });

  const handleDragStart = (sample: Sample) => {
    setDraggedSample(sample);
  };

  const handleDragEnd = () => {
    setDraggedSample(null);
  };

  return (
    <div className="relative py-24 sm:py-32">
      <div className="mx-auto max-w-7xl px-6 lg:px-8">
        <div className="mx-auto max-w-2xl text-center">
          <h2 className="text-base font-semibold leading-7 text-indigo-400">Interactive Demo</h2>
          <p className="mt-2 text-4xl font-bold tracking-tight text-white sm:text-5xl">
            Try the Search Experience
          </p>
          <p className="mt-6 text-lg leading-8 text-slate-300">
            Search, filter, and preview samples in real-time. Drag samples to see the drag-and-drop functionality.
          </p>
        </div>

        <div className="mx-auto mt-16 max-w-6xl">
          <div className="overflow-hidden rounded-3xl border border-slate-800 bg-slate-900/50 shadow-2xl backdrop-blur-sm">
            {/* Search and Filters */}
            <div className="border-b border-slate-800 bg-slate-950/50 p-6">
              <div className="mb-4">
                <div className="relative">
                  <div className="pointer-events-none absolute inset-y-0 left-0 flex items-center pl-4">
                    <svg className="h-5 w-5 text-slate-400" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth={2}>
                      <circle cx="11" cy="11" r="8" />
                      <path d="m21 21-4.35-4.35" />
                    </svg>
                  </div>
                  <input
                    type="text"
                    placeholder="Search samples by name or genre..."
                    value={searchQuery}
                    onChange={(e) => setSearchQuery(e.target.value)}
                    className="w-full rounded-lg border border-slate-700 bg-slate-800/50 py-3 pl-11 pr-4 text-white placeholder-slate-400 focus:border-indigo-500 focus:outline-none focus:ring-2 focus:ring-indigo-500/20"
                  />
                </div>
              </div>

              <div className="grid grid-cols-1 gap-3 sm:grid-cols-3">
                <select
                  value={selectedBpm}
                  onChange={(e) => setSelectedBpm(e.target.value)}
                  className="rounded-lg border border-slate-700 bg-slate-800/50 px-4 py-2 text-white focus:border-indigo-500 focus:outline-none focus:ring-2 focus:ring-indigo-500/20"
                >
                  <option value="">All BPMs</option>
                  <option value="90">90 BPM</option>
                  <option value="120">120 BPM</option>
                  <option value="128">128 BPM</option>
                  <option value="140">140 BPM</option>
                </select>

                <select
                  value={selectedKey}
                  onChange={(e) => setSelectedKey(e.target.value)}
                  className="rounded-lg border border-slate-700 bg-slate-800/50 px-4 py-2 text-white focus:border-indigo-500 focus:outline-none focus:ring-2 focus:ring-indigo-500/20"
                >
                  <option value="">All Keys</option>
                  <option value="C major">C major</option>
                  <option value="A minor">A minor</option>
                  <option value="D minor">D minor</option>
                  <option value="G major">G major</option>
                </select>

                <select
                  value={selectedGenre}
                  onChange={(e) => setSelectedGenre(e.target.value)}
                  className="rounded-lg border border-slate-700 bg-slate-800/50 px-4 py-2 text-white focus:border-indigo-500 focus:outline-none focus:ring-2 focus:ring-indigo-500/20"
                >
                  <option value="">All Genres</option>
                  <option value="Electronic">Electronic</option>
                  <option value="House">House</option>
                  <option value="Drum & Bass">Drum & Bass</option>
                  <option value="Ambient">Ambient</option>
                  <option value="Pop">Pop</option>
                </select>
              </div>
            </div>

            {/* Sample List */}
            <div className="p-6">
              <div className="mb-4 flex items-center justify-between">
                <p className="text-sm text-slate-400">
                  {filteredSamples.length} sample{filteredSamples.length !== 1 ? 's' : ''} found
                </p>
                <button className="text-sm text-indigo-400 hover:text-indigo-300">
                  Clear filters
                </button>
              </div>

              <div className="space-y-3">
                {filteredSamples.map((sample) => (
                  <div
                    key={sample.id}
                    draggable
                    onDragStart={() => handleDragStart(sample)}
                    onDragEnd={handleDragEnd}
                    className={`group cursor-move rounded-xl border border-slate-800 bg-slate-800/30 p-4 transition-all hover:border-indigo-500/50 hover:bg-slate-800/50 ${
                      draggedSample?.id === sample.id ? 'opacity-50' : ''
                    }`}
                  >
                    <div className="flex items-center gap-4">
                      {/* Play Button */}
                      <button className="flex h-10 w-10 flex-shrink-0 items-center justify-center rounded-full bg-gradient-to-br from-indigo-500 to-purple-500 text-white shadow-lg transition-transform hover:scale-110">
                        <svg className="h-4 w-4" viewBox="0 0 24 24" fill="currentColor">
                          <polygon points="5 3 19 12 5 21 5 3" />
                        </svg>
                      </button>

                      {/* Waveform */}
                      <div className="flex flex-1 items-center gap-0.5 overflow-hidden rounded">
                        {sample.waveform.map((height, i) => (
                          <div
                            key={i}
                            className="w-1 bg-gradient-to-t from-indigo-500 to-purple-400 transition-all group-hover:from-indigo-400 group-hover:to-purple-300"
                            style={{ height: `${height * 40}px` }}
                          />
                        ))}
                      </div>

                      {/* Info */}
                      <div className="flex-shrink-0 text-right">
                        <div className="font-semibold text-white">{sample.name}</div>
                        <div className="mt-1 flex items-center gap-3 text-xs text-slate-400">
                          <span className="flex items-center gap-1">
                            <svg className="h-3 w-3" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth={2}>
                              <circle cx="12" cy="12" r="10" />
                              <polyline points="12 6 12 12 16 14" />
                            </svg>
                            {sample.bpm} BPM
                          </span>
                          <span>•</span>
                          <span>{sample.key}</span>
                          <span>•</span>
                          <span>{sample.duration}</span>
                        </div>
                      </div>

                      {/* Drag Icon */}
                      <div className="text-slate-600 transition-colors group-hover:text-slate-400">
                        <svg className="h-5 w-5" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth={2}>
                          <circle cx="9" cy="5" r="1" />
                          <circle cx="9" cy="12" r="1" />
                          <circle cx="9" cy="19" r="1" />
                          <circle cx="15" cy="5" r="1" />
                          <circle cx="15" cy="12" r="1" />
                          <circle cx="15" cy="19" r="1" />
                        </svg>
                      </div>
                    </div>
                  </div>
                ))}
              </div>

              {filteredSamples.length === 0 && (
                <div className="py-12 text-center">
                  <div className="mx-auto mb-4 h-12 w-12 rounded-full bg-slate-800 flex items-center justify-center">
                    <svg className="h-6 w-6 text-slate-600" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth={2}>
                      <circle cx="11" cy="11" r="8" />
                      <path d="m21 21-4.35-4.35" />
                    </svg>
                  </div>
                  <p className="text-slate-400">No samples found matching your criteria</p>
                  <p className="mt-1 text-sm text-slate-500">Try adjusting your filters</p>
                </div>
              )}
            </div>
          </div>

          {/* Drag Drop Zone */}
          <div className="mt-6 rounded-2xl border-2 border-dashed border-slate-800 bg-slate-900/30 p-8 text-center backdrop-blur-sm transition-colors hover:border-slate-700">
            <div className="mx-auto h-16 w-16 rounded-full bg-slate-800 flex items-center justify-center mb-4">
              <svg className="h-8 w-8 text-slate-600" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth={2}>
                <path d="M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4" />
                <polyline points="17 8 12 3 7 8" />
                <line x1="12" y1="3" x2="12" y2="15" />
              </svg>
            </div>
            <p className="text-slate-400">
              {draggedSample ? (
                <>Dropping <span className="font-semibold text-indigo-400">{draggedSample.name}</span> to DAW timeline...</>
              ) : (
                <>Drag samples here to add to your DAW timeline</>
              )}
            </p>
          </div>
        </div>
      </div>
    </div>
  );
}
