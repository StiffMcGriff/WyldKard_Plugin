import { Hero } from './components/Hero';
import { Features } from './components/Features';
import { SampleSearchDemo } from './components/SampleSearchDemo';
import { Footer } from './components/Footer';

export function App() {
  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-950 via-slate-900 to-indigo-950">
      <Hero />
      <Features />
      <SampleSearchDemo />
      <Footer />
    </div>
  );
}
