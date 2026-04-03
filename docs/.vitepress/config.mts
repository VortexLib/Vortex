import { defineConfig } from 'vitepress'

export default defineConfig({
  title: "Vortex",
  description: "High-performance odometry and motion control for VEX Robotics V5.",
  base: '/Vortex/',
  cleanUrls: true,
  appearance: 'dark', // Native dark mode default priority

  themeConfig: {
    logo: '/vortex-icon.svg',
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Guide', link: '/guide/getting-started' },
      { text: 'API Reference', link: '/api/chassis' }
    ],

    sidebar: [
      {
        text: 'Getting Started',
        items: [
          { text: 'Installation', link: '/guide/getting-started' },
          { text: 'Configuration', link: '/guide/configuration' },
        ]
      },
      {
        text: 'API Reference',
        items: [
          { text: 'Chassis Controller', link: '/api/chassis' },
          { text: 'Odometry Metrics', link: '/api/odom' },
          { text: 'Tracking Wheels', link: '/api/tracking-wheels' },
          { text: 'PID Control', link: '/api/pid' },
          { text: 'Piston Control', link: '/api/piston' },
          { text: 'Slew Rate Control', link: '/api/slew' },
          { text: 'Auton Selector', link: '/api/auton-selector' },
          { text: 'SD Card Utilities', link: '/api/sdcard' },
          { text: 'Math & Utilities', link: '/api/utilities' },
        ]
      }
    ],

    socialLinks: [
      { icon: 'github', link: 'https://github.com/jonahchang207/Vortex' }
    ],

    footer: {
      message: 'Released under the MIT License.',
      copyright: 'Copyright © 2026 Vortex Developers'
    },
    
    search: {
      provider: 'local'
    }
  }
})
