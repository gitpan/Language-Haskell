#include "template-hsc.h"
#line 57 "Module.hsc"
#include "HsUnix.h"

int main (int argc, char *argv [])
{
#if __GLASGOW_HASKELL__ && __GLASGOW_HASKELL__ < 409
    printf ("{-# OPTIONS -optc-D__GLASGOW_HASKELL__=%d #-}\n", 603);
#endif
    printf ("{-# OPTIONS %s #-}\n", "-#include \"HsUnix.h\"");
    hsc_line (1, "Module.hsc");
    fputs ("{-# OPTIONS -fffi #-}\n"
           "", stdout);
    hsc_line (2, "Module.hsc");
    fputs ("-----------------------------------------------------------------------------\n"
           "-- |\n"
           "-- Module      :  System.Posix.DynamicLinker.Module\n"
           "-- Copyright   :  (c) Volker Stolz <vs@foldr.org> 2003\n"
           "-- License     :  BSD-style (see the file libraries/base/LICENSE)\n"
           "-- \n"
           "-- Maintainer  :  vs@foldr.org\n"
           "-- Stability   :  provisional\n"
           "-- Portability :  non-portable (requires POSIX)\n"
           "--\n"
           "-- DLOpen support, old API\n"
           "--  Derived from GModule.chs by M.Weber & M.Chakravarty which is part of c2hs\n"
           "--  I left the API more or less the same, mostly the flags are different.\n"
           "--\n"
           "-----------------------------------------------------------------------------\n"
           "\n"
           "module System.Posix.DynamicLinker.Module (\n"
           "\n"
           "--  Usage:\n"
           "--  ******\n"
           "--  \n"
           "--  Let\'s assume you want to open a local shared library \'foo\' (./libfoo.so)\n"
           "--  offering a function\n"
           "--    char * mogrify (char*,int)\n"
           "--  and invoke str = mogrify(\"test\",1):\n"
           "-- \n"
           "--  type Fun = CString -> Int -> IO CString\n"
           "--  foreign import dynamic unsafe fun__ :: FunPtr Fun -> Fun\n"
           "-- \n"
           "--  withModule (Just \".\") (\"libfoo.so\") [RTLD_NOW] $ \\ mod -> do\n"
           "--     funptr <- moduleSymbol mod \"mogrify\"\n"
           "--     let fun = fun__ funptr\n"
           "--     withCString \"test\" $ \\ str -> do\n"
           "--       strptr <- fun str 1\n"
           "--       strstr <- peekCString strptr\n"
           "--       ...\n"
           "\n"
           "      Module\n"
           "    , moduleOpen             -- :: String -> ModuleFlags -> IO Module\n"
           "    , moduleSymbol           -- :: Source -> String -> IO (FunPtr a)\n"
           "    , moduleClose            -- :: Module -> IO Bool\n"
           "    , moduleError            -- :: IO String\n"
           "    , withModule             -- :: Maybe String \n"
           "                             -- -> String \n"
           "\t                     -- -> [ModuleFlags ]\n"
           "\t\t\t     -- -> (Module -> IO a) \n"
           "\t\t\t     -- -> IO a\n"
           "    , withModule_            -- :: Maybe String \n"
           " \t\t\t     -- -> String \n"
           " \t\t\t     -- -> [ModuleFlags] \n"
           " \t\t\t     -- -> (Module -> IO a) \n"
           " \t\t\t     -- -> IO ()\n"
           "    )\n"
           "where\n"
           "\n"
           "", stdout);
    fputs ("\n"
           "", stdout);
    hsc_line (58, "Module.hsc");
    fputs ("\n"
           "import System.Posix.DynamicLinker\n"
           "import Foreign.Ptr\t( Ptr, nullPtr, FunPtr )\n"
           "import Foreign.C.String\t( withCString )\n"
           "\n"
           "-- abstract handle for dynamically loaded module (EXPORTED)\n"
           "--\n"
           "newtype Module = Module (Ptr ())\n"
           "\n"
           "unModule              :: Module -> (Ptr ())\n"
           "unModule (Module adr)  = adr\n"
           "\n"
           "-- Opens a module (EXPORTED)\n"
           "--\n"
           "\n"
           "moduleOpen :: String -> [RTLDFlags] -> IO Module\n"
           "moduleOpen mod flags = do\n"
           "  modPtr <- withCString mod $ \\ modAddr -> c_dlopen modAddr (packRTLDFlags flags)\n"
           "  if (modPtr == nullPtr)\n"
           "      then moduleError >>= \\ err -> ioError (userError (\"dlopen: \" ++ err))\n"
           "      else return $ Module modPtr\n"
           "\n"
           "-- Gets a symbol pointer from a module (EXPORTED)\n"
           "--\n"
           "moduleSymbol :: Module -> String -> IO (FunPtr a)\n"
           "moduleSymbol mod sym = dlsym (DLHandle (unModule mod)) sym\n"
           "\n"
           "-- Closes a module (EXPORTED)\n"
           "-- \n"
           "moduleClose     :: Module -> IO ()\n"
           "moduleClose mod  = dlclose (DLHandle (unModule mod))\n"
           "\n"
           "-- Gets a string describing the last module error (EXPORTED)\n"
           "-- \n"
           "moduleError :: IO String\n"
           "moduleError  = dlerror\n"
           "\n"
           "\n"
           "-- Convenience function, cares for module open- & closing\n"
           "-- additionally returns status of `moduleClose\' (EXPORTED)\n"
           "-- \n"
           "withModule :: Maybe String \n"
           "           -> String \n"
           "\t   -> [RTLDFlags]\n"
           "           -> (Module -> IO a) \n"
           "\t   -> IO a\n"
           "withModule dir mod flags p = do\n"
           "  let modPath = case dir of\n"
           "                  Nothing -> mod\n"
           "\t          Just p  -> p ++ if ((head (reverse p)) == \'/\')\n"
           "                                       then mod\n"
           "\t\t\t\t       else (\'/\':mod)\n"
           "  mod <- moduleOpen modPath flags\n"
           "  result <- p mod\n"
           "  moduleClose mod\n"
           "  return result\n"
           "\n"
           "withModule_ :: Maybe String \n"
           "            -> String \n"
           "\t    -> [RTLDFlags]\n"
           "            -> (Module -> IO a) \n"
           "\t    -> IO ()\n"
           "withModule_ dir mod flags p = withModule dir mod flags p >>= \\ _ -> return ()\n"
           "", stdout);
    return 0;
}
